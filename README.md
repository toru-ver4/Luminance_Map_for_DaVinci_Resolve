# Luminance Map

Luminance Map is a simple effect for DaVinci Resolve, written in DaVinci Color Transform Language (DCTL).

## Description

This effect applies a color map to the HDR signal based on the luminance level, as shown in the figure below.

I created this effect as part of my study of DCTL.

| Original image | ![hoge](https://user-images.githubusercontent.com/3609012/238657074-b99148ee-b12e-483c-81fd-19bbc2f33a6e.png) |
|:----:|:----:|
| Image after applying effect | ![fuga](https://user-images.githubusercontent.com/3609012/238657123-8384a524-74f2-4b8b-8ba1-9ca45ee864e9.png) |

## Demo

[YouTube](https://youtu.be/VU0b3E_Ye_8)

## Getting started

### Requrements

DaVinci Resolve 18.1 or later.

### Install

Copy the `DCTL` directory the DaVinci Resolve's LUT directory.

### Settings for DaVinci Resolve

You should apply these settings unless there are specific reasons not to.

1. Set the gamma of the "Timeline color space" to "ST2084" or "Rec.2100 ST2084."
2. Set both "Input DRT" and "Output DRT" to "None."

| ![fig3](https://user-images.githubusercontent.com/3609012/238667479-a43b7109-b5cf-4fc8-986e-c515ec2b77b8.png) |
|:--------:|
| Fig 3. Suggested configurations for "Color Management"|

This effect functions correctly only with the ST2084 gamma curve.
Moreover, it is strongly recommended to disable DRT,
as the purpose of this effect is to analyze the HDR signal
that has already done color grading.

### Applying the effect

1. Apply the DCTL effect to the HDR video on the timeline.
2. Choose "hdr_luminance_map" from the DCTL List within Effects settings.
3. Set the parameters listed below.

| Parameter name | Description |
|:-----------:|:---------:|
| Start \[cd/m2\] | Specify the luminance range for color map application |
| End \[cd/m2\] | Specify the luminance range for color map application |
| Timeline Color Gamut | Set the same value as "Timeline color space"|
| Judgment Data Type | Choose either "Luminance_RGB2Y" or "Max_Value_Among_RGB" |
| Over Range Color | Choose "Magenta", "Yellow", or "Cyan" |
