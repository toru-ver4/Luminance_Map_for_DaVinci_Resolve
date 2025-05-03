# Luminance Map (7JzCzhz False Color)

Luminance Map (7JzCzhz False Color) is a simple effect for DaVinci Resolve, implemented using DaVinci Color Transform Language (DCTL).

It allows you to create false color effects based on the luminance of HDR10 content.

## Description

This effect applies a false color display to an HDR signal based on its luminance level, as illustrated in the figure below.

I developed this effect as part of my exploration into DCTL.

| Original Image | ![Original Image](https://private-user-images.githubusercontent.com/3609012/440108336-9d91ebae-03f8-4821-98ff-cbbc1fdd33e2.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDYyNjMwNjAsIm5iZiI6MTc0NjI2Mjc2MCwicGF0aCI6Ii8zNjA5MDEyLzQ0MDEwODMzNi05ZDkxZWJhZS0wM2Y4LTQ4MjEtOThmZi1jYmJjMWZkZDMzZTIucG5nP1gtQW16LUFsZ29yaXRobT1BV1M0LUhNQUMtU0hBMjU2JlgtQW16LUNyZWRlbnRpYWw9QUtJQVZDT0RZTFNBNTNQUUs0WkElMkYyMDI1MDUwMyUyRnVzLWVhc3QtMSUyRnMzJTJGYXdzNF9yZXF1ZXN0JlgtQW16LURhdGU9MjAyNTA1MDNUMDg1OTIwWiZYLUFtei1FeHBpcmVzPTMwMCZYLUFtei1TaWduYXR1cmU9YjQzOTVkZWUzYjc2Y2RlNjdjNWYwZWQ5YzcxMmYyNWYyOGY4NTkzNzQ4ODM2YWE1NTUyZmZhY2MwYWI0ZDVhOSZYLUFtei1TaWduZWRIZWFkZXJzPWhvc3QifQ.jvEB5fLbGb2Onn8LIXOVs_S-hmMxOyB2xv-O51hc3tE) |
|:--------------:|:-------------------------------------------------------------------------------------------------:|
| Effect Applied | ![Effect Applied](https://private-user-images.githubusercontent.com/3609012/440108332-bcfd1654-1814-44f9-a06f-e360e9b44135.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NDYyNjMwNjAsIm5iZiI6MTc0NjI2Mjc2MCwicGF0aCI6Ii8zNjA5MDEyLzQ0MDEwODMzMi1iY2ZkMTY1NC0xODE0LTQ0ZjktYTA2Zi1lMzYwZTliNDQxMzUucG5nP1gtQW16LUFsZ29yaXRobT1BV1M0LUhNQUMtU0hBMjU2JlgtQW16LUNyZWRlbnRpYWw9QUtJQVZDT0RZTFNBNTNQUUs0WkElMkYyMDI1MDUwMyUyRnVzLWVhc3QtMSUyRnMzJTJGYXdzNF9yZXF1ZXN0JlgtQW16LURhdGU9MjAyNTA1MDNUMDg1OTIwWiZYLUFtei1FeHBpcmVzPTMwMCZYLUFtei1TaWduYXR1cmU9YzJmYzllZDg4NTVjNzY5MzJjZDBiMDZmYjRhY2VkOTNlYmU0MDhjMjYzNzRmYjBkMjg3OGI0YTQwYThiODE3OSZYLUFtei1TaWduZWRIZWFkZXJzPWhvc3QifQ.KfnbCPfLyKT9VkoBnUmD7b14P5v8F0k_BDUKGFPr640) |

## Demo

Watch the demo on [YouTube](https://youtu.be/CVPQD-OdkGU).

[![Watch the demo](https://img.youtube.com/vi/CVPQD-OdkGU/0.jpg)](https://youtu.be/CVPQD-OdkGU)

## Getting started

### Requrements

- DaVinci Resolve 19.1 or later.

### Installation

Copy the `DCTL` directory into DaVinci Resolve's LUT directory.

* Windows: `C:\ProgramData\Blackmagic Design\DaVinci Resolve\Support\LUT`
* macOS: `/Library/Application Support/Blackmagic Design/DaVinci Resolve/LUT`

### DaVinci Resolve Settings

Unless you have a specific reason not to, apply the following settings:

1. Set the gamma for the "Timeline Color Space" to either "ST2084" or "Rec.2100 ST2084."
2. Set both "Input DRT" and "Output DRT" to "None."

| ![Recommended Settings](https://user-images.githubusercontent.com/3609012/238667479-a43b7109-b5cf-4fc8-986e-c515ec2b77b8.png) |
|:---------------------------------------------------------------------------------------------------------------------:|
| *Recommended configuration for "Color Management"* |

**Note:** This effect works correctly only with the ST2084 gamma curve. It is also strongly recommended to disable DRT, as the purpose of this effect is to analyze an HDR signal that has already been color graded.

### Applying the effect

1. Apply the DCTL effect to your HDR video on the timeline.
2. Select "hdr_luminance_map" from the DCTL list in the Effects settings.
3. Configure the following parameters:

| Parameter Name        | Description                                                                     |
|-----------------------|---------------------------------------------------------------------------------|
| Timeline Color Gamut  | Set this value to match your "Timeline Color Space."                            |
| Judgment Data Type    | Choose between "Luminance_RGB2Y" and "Max_Value_Among_RGB."                     |
