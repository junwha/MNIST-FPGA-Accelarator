# MNIST-FPGA-Accelarator 

## Description
This is a project for accelerating MNIST classification using FPGA pynq board. We implemented streaming architecture using 1-bit quantization. As the result, our hardware is currently about 10x faster than numpy for MNIST classification. 

## Hierarchy
`src`: vivado HLS source code for main hardware

`MNIST-accelerator-comparison.ipynb`: An example for comparing the speed of hardware and numpy

`preprocess.ipynb`: with this file, you can preprocess weights or preprocess dataset for specific batch size


## Top diagram
![top_diagram](https://user-images.githubusercontent.com/17183234/170824465-58e4b5a0-73f0-42be-8a03-7c299c84c48a.PNG)


