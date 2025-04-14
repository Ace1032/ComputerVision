# Motion Detection Using Frame Differencing in OpenCV

This project demonstrates real-time motion detection using OpenCV by comparing consecutive grayscale frames captured from a webcam.

## What It Does

- Captures video from the default webcam
- Converts each frame to grayscale
- Computes the absolute difference between the current and previous grayscale frames
- Calculates the percentage of the image that changed
- Displays:
  - Current frame (`Gray Example`)
  - Previous frame (`Gray Previous`)
  - Difference frame with motion highlights (`Gray Diff`)
- Highlights motion with a numeric diff overlay if changes exceed a threshold

## Core Concepts

- **Grayscale Conversion** using `cv::cvtColor`
- **Frame Differencing** using `cv::absdiff`
- **Sum of Differences** using `cv::sum`
- **Motion Thresholding**
- **Overlaying Text** using `cv::putText`

## Use Cases
- Motion-triggered surveillance systems
- Preprocessing for object tracking
- Activity monitoring in robotics
- Experiment visualization (physics/biology)

---

## Requirements
- OpenCV 4+
- C++ Compiler (e.g., `g++`)
- `pkg-config` (for OpenCV build flags)
