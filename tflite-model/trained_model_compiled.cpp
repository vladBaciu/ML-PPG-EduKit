/* Generated by Edge Impulse
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
// Generated on: 30.11.2022 21:04:31

#include <stdio.h>
#include <stdlib.h>
#include "edge-impulse-sdk/tensorflow/lite/c/builtin_op_data.h"
#include "edge-impulse-sdk/tensorflow/lite/c/common.h"
#include "edge-impulse-sdk/tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"

#if EI_CLASSIFIER_PRINT_STATE
#if defined(__cplusplus) && EI_C_LINKAGE == 1
extern "C" {
    extern void ei_printf(const char *format, ...);
}
#else
extern void ei_printf(const char *format, ...);
#endif
#endif

#if defined __GNUC__
#define ALIGN(X) __attribute__((aligned(X)))
#elif defined _MSC_VER
#define ALIGN(X) __declspec(align(X))
#elif defined __TASKING__
#define ALIGN(X) __align(X)
#endif

#ifndef EI_MAX_SCRATCH_BUFFER_COUNT
#define EI_MAX_SCRATCH_BUFFER_COUNT 4
#endif // EI_MAX_SCRATCH_BUFFER_COUNT

#ifndef EI_MAX_OVERFLOW_BUFFER_COUNT
#define EI_MAX_OVERFLOW_BUFFER_COUNT 10
#endif // EI_MAX_OVERFLOW_BUFFER_COUNT

using namespace tflite;
using namespace tflite::ops;
using namespace tflite::ops::micro;

namespace {

constexpr int kTensorArenaSize = 256;

#if defined(EI_CLASSIFIER_ALLOCATION_STATIC)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX)
#pragma Bss(".tensor_arena")
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16);
#pragma Bss()
#elif defined(EI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU)
uint8_t tensor_arena[kTensorArenaSize] ALIGN(16) __attribute__((section(".tensor_arena")));
#else
#define EI_CLASSIFIER_ALLOCATION_HEAP 1
uint8_t* tensor_arena = NULL;
#endif

static uint8_t* tensor_boundary;
static uint8_t* current_location;

template <int SZ, class T> struct TfArray {
  int sz; T elem[SZ];
};
enum used_operators_e {
  OP_FULLY_CONNECTED, OP_SOFTMAX,  OP_LAST
};
struct TensorInfo_t { // subset of TfLiteTensor used for initialization from constant memory
  TfLiteAllocationType allocation_type;
  TfLiteType type;
  void* data;
  TfLiteIntArray* dims;
  size_t bytes;
  TfLiteQuantization quantization;
};
struct NodeInfo_t { // subset of TfLiteNode used for initialization from constant memory
  struct TfLiteIntArray* inputs;
  struct TfLiteIntArray* outputs;
  void* builtin_data;
  used_operators_e used_op_index;
};

TfLiteContext ctx{};
TfLiteTensor tflTensors[11];
TfLiteEvalTensor tflEvalTensors[11];
TfLiteRegistration registrations[OP_LAST];
TfLiteNode tflNodes[4];

const TfArray<2, int> tensor_dimension0 = { 2, { 1,21 } };
const TfArray<1, float> quant0_scale = { 1, { 11.774564743041992, } };
const TfArray<1, int> quant0_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant0 = { (TfLiteFloatArray*)&quant0_scale, (TfLiteIntArray*)&quant0_zero, 0 };
const ALIGN(16) int8_t tensor_data1[20*21] = { 
  -98, -90, -81, 10, -26, 6, -104, -97, -102, 14, 109, -68, -90, 113, 47, 120, 109, -45, 81, -85, 111, 
  14, 25, -1, -51, 23, 116, 83, 100, -105, 80, 64, -62, -29, -104, -74, -54, -50, -108, 84, 55, -6, 
  -1, -124, -99, 53, 0, 28, -120, -30, -79, 13, -42, -31, -93, -28, 67, -105, -86, -30, 105, -121, 85, 
  -123, -34, -100, 52, 33, 37, -88, 19, 19, 108, 1, -109, 20, 56, 11, -62, -34, -27, 119, 74, -126, 
  1, 71, -76, 79, 40, 112, -96, -49, 24, 39, 42, 4, -8, -26, -107, -5, -62, -56, 29, 23, 20, 
  66, -68, -21, -18, 0, 51, 28, 45, 0, -102, -59, -75, 120, -62, 95, 26, -62, 48, 88, 110, -64, 
  -90, 119, -12, -41, -56, 44, 42, -24, -54, 71, -100, -103, -118, -85, 113, 35, -22, 64, 27, -38, 27, 
  -42, 123, -85, -29, -104, 116, 18, -117, 101, -98, 79, -68, -91, -55, -70, -13, -2, -99, 7, -36, -39, 
  39, 51, 47, -121, 78, 58, -40, -25, 52, -99, -125, 119, 9, -49, -127, -78, 22, -22, 91, -1, -15, 
  -6, 20, 16, 63, -104, -7, -16, -47, 60, -18, 6, -35, -62, -11, 9, -56, 36, 111, 108, -102, 75, 
  -101, -104, -120, -95, 119, -43, 41, -4, 17, 85, 9, 107, 24, 106, -15, -92, -79, 77, -39, -13, -68, 
  105, 73, -9, -23, 7, 126, 38, 88, 101, 114, -29, 98, 18, -80, -74, 59, 16, 74, 91, 93, 67, 
  51, 84, 26, -68, 103, -39, 28, -52, -21, 121, -5, -56, -89, 99, 113, -122, 68, -5, -115, -25, -121, 
  9, 28, -42, 80, 11, -36, 63, -29, 36, 89, 117, 105, 56, -51, 1, 23, -79, -70, 29, 97, -121, 
  -75, -125, 125, -60, 60, -43, 64, 78, 12, -46, -106, -22, -103, -34, 13, -20, -68, -57, -54, -74, 27, 
  -77, 125, -42, 43, -37, 112, -70, -62, -13, 98, -75, 52, -48, -30, 126, -92, -11, 87, 72, 88, 34, 
  -91, 107, 80, 25, 0, 2, -18, -56, -17, 44, 9, -97, -69, -117, -78, 60, 92, 64, -100, -12, -63, 
  -56, 7, -120, -108, 111, -53, 21, 90, -72, 10, 11, 54, 27, -38, -20, -37, 6, -20, -66, 100, -115, 
  -85, -27, 101, 110, 76, 48, -3, -86, -34, -32, -107, -85, 93, -13, -55, 88, -50, -21, -105, -21, 79, 
  -41, 52, 82, 55, 24, -11, -3, -113, 106, 110, -35, 93, -16, -42, 100, 37, 25, -122, 33, -25, -42, 
};
const TfArray<2, int> tensor_dimension1 = { 2, { 20,21 } };
const TfArray<1, float> quant1_scale = { 1, { 0.0030017327517271042, } };
const TfArray<1, int> quant1_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant1 = { (TfLiteFloatArray*)&quant1_scale, (TfLiteIntArray*)&quant1_zero, 0 };
const ALIGN(16) int32_t tensor_data2[20] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
const TfArray<1, int> tensor_dimension2 = { 1, { 20 } };
const TfArray<1, float> quant2_scale = { 1, { 0.035344097763299942, } };
const TfArray<1, int> quant2_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant2 = { (TfLiteFloatArray*)&quant2_scale, (TfLiteIntArray*)&quant2_zero, 0 };
const ALIGN(16) int8_t tensor_data3[10*20] = { 
  -78, -4, 35, 21, 103, -74, -33, 21, -104, -113, -39, -68, 111, 100, -34, 1, -107, 17, -36, 15, 
  -80, 18, -62, 48, 30, 11, 86, -54, -45, -89, 20, -95, -29, -38, -95, -106, -51, 81, 59, -105, 
  -96, 85, 30, -62, 79, -2, 52, -54, 97, 93, -72, -56, 39, -117, 39, -40, -28, 121, -109, -36, 
  -78, -23, -75, -101, -18, 60, 82, 93, 108, -87, 95, 52, 6, -75, -29, 124, 30, 35, 32, -79, 
  18, 8, -66, -93, -122, 106, -43, -7, -73, 121, 6, -120, -106, 45, -19, 23, 23, -110, 120, 29, 
  71, 98, -98, 11, -85, -20, 7, -28, 116, -117, -126, 114, -98, 54, -62, 93, -108, -10, -106, 83, 
  94, -39, 14, 97, 77, -30, 19, 57, 52, 104, -60, 70, -127, -14, -8, -14, 47, -26, 45, -59, 
  -63, 112, -69, -117, -25, -24, -40, -100, 107, 83, 79, 116, -18, -3, -28, -44, -68, 20, -51, 58, 
  -88, 78, 9, 57, 114, 0, 73, -118, -26, -90, 51, 88, 105, 119, -20, 55, -100, 111, -2, 1, 
  -29, 42, 26, 95, -90, 69, 83, -68, 93, -41, -24, 40, -100, -37, -100, 30, 123, 115, -41, 118, 
};
const TfArray<2, int> tensor_dimension3 = { 2, { 10,20 } };
const TfArray<1, float> quant3_scale = { 1, { 0.0034941192716360092, } };
const TfArray<1, int> quant3_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant3 = { (TfLiteFloatArray*)&quant3_scale, (TfLiteIntArray*)&quant3_zero, 0 };
const ALIGN(16) int32_t tensor_data4[10] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, };
const TfArray<1, int> tensor_dimension4 = { 1, { 10 } };
const TfArray<1, float> quant4_scale = { 1, { 0.026969224214553833, } };
const TfArray<1, int> quant4_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant4 = { (TfLiteFloatArray*)&quant4_scale, (TfLiteIntArray*)&quant4_zero, 0 };
const ALIGN(16) int8_t tensor_data5[2*10] = { 
  -38, -127, -11, -117, 8, -83, 55, 81, 3, 48, 
  74, -114, -12, 109, 103, 66, 62, -6, 28, -4, 
};
const TfArray<2, int> tensor_dimension5 = { 2, { 2,10 } };
const TfArray<1, float> quant5_scale = { 1, { 0.0055145043879747391, } };
const TfArray<1, int> quant5_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant5 = { (TfLiteFloatArray*)&quant5_scale, (TfLiteIntArray*)&quant5_zero, 0 };
const ALIGN(8) int32_t tensor_data6[2] = { 0, 0, };
const TfArray<1, int> tensor_dimension6 = { 1, { 2 } };
const TfArray<1, float> quant6_scale = { 1, { 0.019424170255661011, } };
const TfArray<1, int> quant6_zero = { 1, { 0 } };
const TfLiteAffineQuantization quant6 = { (TfLiteFloatArray*)&quant6_scale, (TfLiteIntArray*)&quant6_zero, 0 };
const TfArray<2, int> tensor_dimension7 = { 2, { 1,20 } };
const TfArray<1, float> quant7_scale = { 1, { 7.7184610366821289, } };
const TfArray<1, int> quant7_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant7 = { (TfLiteFloatArray*)&quant7_scale, (TfLiteIntArray*)&quant7_zero, 0 };
const TfArray<2, int> tensor_dimension8 = { 2, { 1,10 } };
const TfArray<1, float> quant8_scale = { 1, { 3.5223782062530518, } };
const TfArray<1, int> quant8_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant8 = { (TfLiteFloatArray*)&quant8_scale, (TfLiteIntArray*)&quant8_zero, 0 };
const TfArray<2, int> tensor_dimension9 = { 2, { 1,2 } };
const TfArray<1, float> quant9_scale = { 1, { 1.6369756460189819, } };
const TfArray<1, int> quant9_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant9 = { (TfLiteFloatArray*)&quant9_scale, (TfLiteIntArray*)&quant9_zero, 0 };
const TfArray<2, int> tensor_dimension10 = { 2, { 1,2 } };
const TfArray<1, float> quant10_scale = { 1, { 0.00390625, } };
const TfArray<1, int> quant10_zero = { 1, { -128 } };
const TfLiteAffineQuantization quant10 = { (TfLiteFloatArray*)&quant10_scale, (TfLiteIntArray*)&quant10_zero, 0 };
const TfLiteFullyConnectedParams opdata0 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs0 = { 3, { 0,1,2 } };
const TfArray<1, int> outputs0 = { 1, { 7 } };
const TfLiteFullyConnectedParams opdata1 = { kTfLiteActRelu, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs1 = { 3, { 7,3,4 } };
const TfArray<1, int> outputs1 = { 1, { 8 } };
const TfLiteFullyConnectedParams opdata2 = { kTfLiteActNone, kTfLiteFullyConnectedWeightsFormatDefault, false, false };
const TfArray<3, int> inputs2 = { 3, { 8,5,6 } };
const TfArray<1, int> outputs2 = { 1, { 9 } };
const TfLiteSoftmaxParams opdata3 = { 1 };
const TfArray<1, int> inputs3 = { 1, { 9 } };
const TfArray<1, int> outputs3 = { 1, { 10 } };
const TensorInfo_t tensorData[] = {
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 32, (TfLiteIntArray*)&tensor_dimension0, 21, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant0))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data1, (TfLiteIntArray*)&tensor_dimension1, 420, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant1))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data2, (TfLiteIntArray*)&tensor_dimension2, 80, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant2))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data3, (TfLiteIntArray*)&tensor_dimension3, 200, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant3))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data4, (TfLiteIntArray*)&tensor_dimension4, 40, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant4))}, },
  { kTfLiteMmapRo, kTfLiteInt8, (void*)tensor_data5, (TfLiteIntArray*)&tensor_dimension5, 20, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant5))}, },
  { kTfLiteMmapRo, kTfLiteInt32, (void*)tensor_data6, (TfLiteIntArray*)&tensor_dimension6, 8, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant6))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension7, 20, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant7))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 32, (TfLiteIntArray*)&tensor_dimension8, 10, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant8))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 16, (TfLiteIntArray*)&tensor_dimension9, 2, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant9))}, },
  { kTfLiteArenaRw, kTfLiteInt8, tensor_arena + 0, (TfLiteIntArray*)&tensor_dimension10, 2, {kTfLiteAffineQuantization, const_cast<void*>(static_cast<const void*>(&quant10))}, },
};const NodeInfo_t nodeData[] = {
  { (TfLiteIntArray*)&inputs0, (TfLiteIntArray*)&outputs0, const_cast<void*>(static_cast<const void*>(&opdata0)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs1, (TfLiteIntArray*)&outputs1, const_cast<void*>(static_cast<const void*>(&opdata1)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs2, (TfLiteIntArray*)&outputs2, const_cast<void*>(static_cast<const void*>(&opdata2)), OP_FULLY_CONNECTED, },
  { (TfLiteIntArray*)&inputs3, (TfLiteIntArray*)&outputs3, const_cast<void*>(static_cast<const void*>(&opdata3)), OP_SOFTMAX, },
};
static void* overflow_buffers[EI_MAX_OVERFLOW_BUFFER_COUNT];
static size_t overflow_buffers_ix = 0;
static void * AllocatePersistentBuffer(struct TfLiteContext* ctx,
                                       size_t bytes) {
  void *ptr;
  if (current_location - bytes < tensor_boundary) {
    if (overflow_buffers_ix > EI_MAX_OVERFLOW_BUFFER_COUNT - 1) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d, does not fit in tensor arena and reached EI_MAX_OVERFLOW_BUFFER_COUNT\n",
        (int)bytes);
      return NULL;
    }

    // OK, this will look super weird, but.... we have CMSIS-NN buffers which
    // we cannot calculate beforehand easily.
    ptr = ei_calloc(bytes, 1);
    if (ptr == NULL) {
      ei_printf("ERR: Failed to allocate persistent buffer of size %d\n", (int)bytes);
      return NULL;
    }
    overflow_buffers[overflow_buffers_ix++] = ptr;
    return ptr;
  }

  current_location -= bytes;

  ptr = current_location;
  memset(ptr, 0, bytes);

  return ptr;
}
typedef struct {
  size_t bytes;
  void *ptr;
} scratch_buffer_t;
static scratch_buffer_t scratch_buffers[EI_MAX_SCRATCH_BUFFER_COUNT];
static size_t scratch_buffers_ix = 0;

static TfLiteStatus RequestScratchBufferInArena(struct TfLiteContext* ctx, size_t bytes,
                                                int* buffer_idx) {
  if (scratch_buffers_ix > EI_MAX_SCRATCH_BUFFER_COUNT - 1) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d, reached EI_MAX_SCRATCH_BUFFER_COUNT\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffer_t b;
  b.bytes = bytes;

  b.ptr = AllocatePersistentBuffer(ctx, b.bytes);
  if (!b.ptr) {
    ei_printf("ERR: Failed to allocate scratch buffer of size %d\n",
      (int)bytes);
    return kTfLiteError;
  }

  scratch_buffers[scratch_buffers_ix] = b;
  *buffer_idx = scratch_buffers_ix;

  scratch_buffers_ix++;

  return kTfLiteOk;
}

static void* GetScratchBuffer(struct TfLiteContext* ctx, int buffer_idx) {
  if (buffer_idx > (int)scratch_buffers_ix) {
    return NULL;
  }
  return scratch_buffers[buffer_idx].ptr;
}

static TfLiteTensor* GetTensor(const struct TfLiteContext* context,
                               int tensor_idx) {
  return &tflTensors[tensor_idx];
}

static TfLiteEvalTensor* GetEvalTensor(const struct TfLiteContext* context,
                                       int tensor_idx) {
  return &tflEvalTensors[tensor_idx];
}

} // namespace

TfLiteStatus trained_model_init( void*(*alloc_fnc)(size_t,size_t) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  tensor_arena = (uint8_t*) alloc_fnc(16, kTensorArenaSize);
  if (!tensor_arena) {
    ei_printf("ERR: failed to allocate tensor arena\n");
    return kTfLiteError;
  }
#else
  memset(tensor_arena, 0, kTensorArenaSize);
#endif
  tensor_boundary = tensor_arena;
  current_location = tensor_arena + kTensorArenaSize;
  ctx.AllocatePersistentBuffer = &AllocatePersistentBuffer;
  ctx.RequestScratchBufferInArena = &RequestScratchBufferInArena;
  ctx.GetScratchBuffer = &GetScratchBuffer;
  ctx.GetTensor = &GetTensor;
  ctx.GetEvalTensor = &GetEvalTensor;
  ctx.tensors = tflTensors;
  ctx.tensors_size = 11;
  for (size_t i = 0; i < 11; ++i) {
    tflTensors[i].type = tensorData[i].type;
    tflEvalTensors[i].type = tensorData[i].type;
    tflTensors[i].is_variable = 0;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
    tflTensors[i].allocation_type = tensorData[i].allocation_type;
#else
    tflTensors[i].allocation_type = (tensor_arena <= tensorData[i].data && tensorData[i].data < tensor_arena + kTensorArenaSize) ? kTfLiteArenaRw : kTfLiteMmapRo;
#endif
    tflTensors[i].bytes = tensorData[i].bytes;
    tflTensors[i].dims = tensorData[i].dims;
    tflEvalTensors[i].dims = tensorData[i].dims;

#if defined(EI_CLASSIFIER_ALLOCATION_HEAP)
    if(tflTensors[i].allocation_type == kTfLiteArenaRw){
      uint8_t* start = (uint8_t*) ((uintptr_t)tensorData[i].data + (uintptr_t) tensor_arena);

     tflTensors[i].data.data =  start;
     tflEvalTensors[i].data.data =  start;
    }
    else {
       tflTensors[i].data.data = tensorData[i].data;
       tflEvalTensors[i].data.data = tensorData[i].data;
    }
#else
    tflTensors[i].data.data = tensorData[i].data;
    tflEvalTensors[i].data.data = tensorData[i].data;
#endif // EI_CLASSIFIER_ALLOCATION_HEAP
    tflTensors[i].quantization = tensorData[i].quantization;
    if (tflTensors[i].quantization.type == kTfLiteAffineQuantization) {
      TfLiteAffineQuantization const* quant = ((TfLiteAffineQuantization const*)(tensorData[i].quantization.params));
      tflTensors[i].params.scale = quant->scale->data[0];
      tflTensors[i].params.zero_point = quant->zero_point->data[0];
    }
    if (tflTensors[i].allocation_type == kTfLiteArenaRw) {
      auto data_end_ptr = (uint8_t*)tflTensors[i].data.data + tensorData[i].bytes;
      if (data_end_ptr > tensor_boundary) {
        tensor_boundary = data_end_ptr;
      }
    }
  }
  if (tensor_boundary > current_location /* end of arena size */) {
    ei_printf("ERR: tensor arena is too small, does not fit model - even without scratch buffers\n");
    return kTfLiteError;
  }
  registrations[OP_FULLY_CONNECTED] = Register_FULLY_CONNECTED();
  registrations[OP_SOFTMAX] = Register_SOFTMAX();

  for (size_t i = 0; i < 4; ++i) {
    tflNodes[i].inputs = nodeData[i].inputs;
    tflNodes[i].outputs = nodeData[i].outputs;
    tflNodes[i].builtin_data = nodeData[i].builtin_data;
tflNodes[i].custom_initial_data = nullptr;
      tflNodes[i].custom_initial_data_size = 0;
if (registrations[nodeData[i].used_op_index].init) {
      tflNodes[i].user_data = registrations[nodeData[i].used_op_index].init(&ctx, (const char*)tflNodes[i].builtin_data, 0);
    }
  }
  for (size_t i = 0; i < 4; ++i) {
    if (registrations[nodeData[i].used_op_index].prepare) {
      TfLiteStatus status = registrations[nodeData[i].used_op_index].prepare(&ctx, &tflNodes[i]);
      if (status != kTfLiteOk) {
        return status;
      }
    }
  }
  return kTfLiteOk;
}

static const int inTensorIndices[] = {
  0, 
};
TfLiteTensor* trained_model_input(int index) {
  return &ctx.tensors[inTensorIndices[index]];
}

static const int outTensorIndices[] = {
  10, 
};
TfLiteTensor* trained_model_output(int index) {
  return &ctx.tensors[outTensorIndices[index]];
}

TfLiteStatus trained_model_invoke() {
  for (size_t i = 0; i < 4; ++i) {
    TfLiteStatus status = registrations[nodeData[i].used_op_index].invoke(&ctx, &tflNodes[i]);

#if EI_CLASSIFIER_PRINT_STATE
    ei_printf("layer %lu\n", i);
    ei_printf("    inputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].inputs->size; ix++) {
      auto d = tensorData[tflNodes[i].inputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");

    ei_printf("    outputs:\n");
    for (size_t ix = 0; ix < tflNodes[i].outputs->size; ix++) {
      auto d = tensorData[tflNodes[i].outputs->data[ix]];

      size_t data_ptr = (size_t)d.data;

      if (d.allocation_type == kTfLiteArenaRw) {
        data_ptr = (size_t)tensor_arena + data_ptr;
      }

      if (d.type == TfLiteType::kTfLiteInt8) {
        int8_t* data = (int8_t*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes; jx++) {
          ei_printf("%d ", data[jx]);
        }
      }
      else {
        float* data = (float*)data_ptr;
        ei_printf("        %lu (%zu bytes, ptr=%p, alloc_type=%d, type=%d): ", ix, d.bytes, data, (int)d.allocation_type, (int)d.type);
        for (size_t jx = 0; jx < d.bytes / 4; jx++) {
          ei_printf("%f ", data[jx]);
        }
      }
      ei_printf("\n");
    }
    ei_printf("\n");
#endif // EI_CLASSIFIER_PRINT_STATE

    if (status != kTfLiteOk) {
      return status;
    }
  }
  return kTfLiteOk;
}

TfLiteStatus trained_model_reset( void (*free_fnc)(void* ptr) ) {
#ifdef EI_CLASSIFIER_ALLOCATION_HEAP
  free_fnc(tensor_arena);
#endif

  // scratch buffers are allocated within the arena, so just reset the counter so memory can be reused
  scratch_buffers_ix = 0;

  // overflow buffers are on the heap, so free them first
  for (size_t ix = 0; ix < overflow_buffers_ix; ix++) {
    ei_free(overflow_buffers[ix]);
  }
  overflow_buffers_ix = 0;
  return kTfLiteOk;
}
