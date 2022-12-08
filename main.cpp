#include <stdio.h>
#include <stdarg.h>
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"`
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

#include "ppg_config.h"
#include "ppg_mtb_adc.h"

#define EI_PORTING_INFINEONPSOC62 1
// Callback function declaration
static int get_signal_data(size_t offset, size_t length, float *out_ptr);

// Raw features copied from test sample
static const float features[] = {
377, 273, 667, 380, 276, 667, 380, 275, 663, 379, 268, 663, 373, 263, 658, 370, 261, 656, 368, 261, 657, 366, 260, 654, 369, 258, 654, 367, 257, 650, 365, 252, 649, 361, 250, 649, 359, 250, 645, 358, 246, 644, 354, 244, 643, 360, 251, 650, 371, 266, 662, 377, 276, 665, 382, 276, 667, 379, 272, 660, 375, 265, 656, 369, 258, 654, 364, 258, 650, 368, 258, 652, 363, 254, 649, 362, 254, 647, 360, 250, 647, 356, 247, 645, 356, 245, 643, 352, 243, 641, 350, 241, 638, 351, 241, 641, 360, 256, 654, 374, 270, 662, 377, 276, 666, 377, 275, 664, 376, 268, 662, 372, 265, 655, 368, 256, 652, 366, 257, 651, 362, 257, 649, 364, 255, 650, 362, 254, 648, 360, 249, 646, 359, 245, 644, 356, 248, 642, 355, 244, 642, 353, 242, 638, 352, 243, 639, 359, 253, 652, 369, 269, 661, 379, 274, 665, 378, 272, 661, 376, 269, 658, 372, 263, 656, 366, 259, 652, 364, 255, 651, 360, 255, 650, 360, 255, 645, 362, 251, 648, 359, 251, 646, 358, 247, 644, 354, 245, 643, 350, 243, 640, 352, 238, 638, 351, 242, 641, 358, 252, 650, 367, 263, 659, 372, 269, 659, 375, 265, 660, 371, 262, 650, 367, 255, 650
};

int main(int argc, char **argv) {
	cy_rslt_t result_init;
    signal_t signal;            // Wrapper for raw input buffer
    ei_impulse_result_t result; // Used to store inference output
    EI_IMPULSE_ERROR res;       // Return code from inference

    /* Initialize the device and board peripherals */
    result_init = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result_init != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
    result_init = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                                 CY_RETARGET_IO_BAUDRATE);

    /* retarget-io init failed. Stop program execution */
    if (result_init != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

#if (MAIN_APP == PPG_APP_EI_STREAM_DATA)
    PPG_AppStreamingData();
#endif

    // Calculate the length of the buffer
    size_t buf_len = sizeof(features) / sizeof(features[0]);

    // Make sure that the length of the buffer matches expected input length
    if (buf_len != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
        ei_printf("ERROR: The size of the input buffer is not correct.\r\n");
        ei_printf("Expected %d items, but got %d\r\n",
                EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE,
                (int)buf_len);
        return 1;
    }

    // Assign callback function to fill buffer used for preprocessing/inference
    signal.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
    signal.get_data = &get_signal_data;

    // Perform DSP pre-processing and inference
    res = run_classifier(&signal, &result, false);

    // Print return code and how long it took to perform inference
    ei_printf("run_classifier returned: %d\r\n", res);
    ei_printf("Timing: DSP %d ms, inference %d ms, anomaly %d ms\r\n",
            result.timing.dsp,
            result.timing.classification,
            result.timing.anomaly);

    // Print the prediction results (object detection)
#if EI_CLASSIFIER_OBJECT_DETECTION == 1
    ei_printf("Object detection bounding boxes:\r\n");
    for (uint32_t i = 0; i < result.bounding_boxes_count; i++) {
        ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];
        if (bb.value == 0) {
            continue;
        }
        ei_printf("  %s (%f) [ x: %u, y: %u, width: %u, height: %u ]\r\n",
                bb.label,
                bb.value,
                bb.x,
                bb.y,
                bb.width,
                bb.height);
    }

    // Print the prediction results (classification)
#else
    ei_printf("Predictions:\r\n");
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        ei_printf("  %s: ", ei_classifier_inferencing_categories[i]);
        ei_printf("%.5f\r\n", result.classification[i].value);
    }
#endif

    // Print anomaly result (if it exists)
#if EI_CLASSIFIER_HAS_ANOMALY == 1
    ei_printf("Anomaly prediction: %.3f\r\n", result.anomaly);
#endif

    return 0;
}

// Callback: fill a section of the out_ptr buffer when requested
static int get_signal_data(size_t offset, size_t length, float *out_ptr) {
    for (size_t i = 0; i < length; i++) {
        out_ptr[i] = (features + offset)[i];
    }

    return EIDSP_OK;
}


void ei_printf(const char *format, ...) {
    static char print_buf[1024] = { 0 };

    va_list args;
    va_start(args, format);
    int r = vsnprintf(print_buf, sizeof(print_buf), format, args);
    va_end(args);


}
