# ppg-edu-kit-edge-impulse-mtb

[![DeepSource](https://deepsource.io/gh/vladBaciu/ppg-edu-kit-edge-impulse-mtb.svg/?label=active+issues&show_trend=true&token=kAoz_Mu1cturth8eQ9ygMEbv)](https://deepsource.io/gh/vladBaciu/ppg-edu-kit-edge-impulse-mtb/?ref=repository-badge)


## Stream data to edge impulse

**Prerequisite**: install [Edge Impulse CLI](https://docs.edgeimpulse.com/docs/edge-impulse-cli/cli-installation) in order to communicate with PPG EduKit.

Any Edge Impulse Device could send data over serial using the data forwarder. The [data forwarder](https://docs.edgeimpulse.com/docs/edge-impulse-cli/cli-data-forwarder) collects the data, signs the data and sends the data to the ingestion service. The data forwarder is useful to quickly enable data collection from a wide variety of development boards without having to port the full remote management protocol and serial protocol, but only supports collecting data at relatively low frequencies.

Set the ```MAIN_APP_TYPE``` make variable accordingly. Build the streaming application by executing ```make build``` in project directory.

![image](https://user-images.githubusercontent.com/24388880/208964145-04b37a6d-5e2c-4e0f-9902-773d9b3bfd78.png) 

<details>
<summary>Output</summary>

![image](https://user-images.githubusercontent.com/24388880/208968099-aac78298-ded0-4a7c-9f6d-3c6ac9758580.png)

</details>

Execute ```make program``` and flash the board. 


Now the board is streaming the data over serial and data-forwarder can be launched from the command line by executing ```edge-impulse-data-forwarder```. If it is the first time you launch this tool, follow the steps from [here](https://docs.edgeimpulse.com/docs/edge-impulse-cli/cli-data-forwarder).

**Note**: To skip the compilation stage, in ```others``` directory there is a binary image that can be directly flashed using the PSoC Programmer tool.

<details>
<summary>Output</summary>

![image](https://user-images.githubusercontent.com/24388880/208968643-039311fa-fa6d-4761-9614-417369840129.png)
![image](https://user-images.githubusercontent.com/24388880/208968375-5232d41a-5a97-41c9-9000-d9926c0c05d6.png)

</details>

Now go to your Edge Impulse project, connect the device and start training your ML model. 

<details>
<summary>Output</summary>
An anomaly detection model was trained to determine if the recorded PPG signal contains any artifacts.

![image](https://user-images.githubusercontent.com/24388880/208969320-3ca8c549-aa8f-446f-9ac3-ae15bb8ebe3b.png)

</details>

## On target inference

The anomaly detection model created earlier can be deployed as a C++ library. Edge Impulse does this for you (https://docs.edgeimpulse.com/docs/deployment/running-your-impulse-locally). I downloaded the model in the current directory (model-parameters, edge-impulse-sdk and tflite-model). After some updates in the makefile, the EI library could be compiled and used in the project.

Go to the Makefile and set the ```MAIN_APP_TYPE``` variable as 1. Run ```make build```. This will compile the demo application that performs live inference on the measured PPG signal. Run ```make program``` and flash the board.

![image](https://user-images.githubusercontent.com/24388880/208971955-5a5f0975-c4de-4e53-ba7e-f39462a85429.png)

[Tauno Serial Plotter](https://github.com/taunoe/tauno-serial-plotter) can be used to visualize the classification results in real-time. The red signal represents the model anomaly class (0 - Anomaly, 1 - Normal).


![Untitled video - Made with Clipchamp](https://user-images.githubusercontent.com/24388880/208976992-66f7d82f-46a1-4fcd-9c6d-283162365e3b.gif)



