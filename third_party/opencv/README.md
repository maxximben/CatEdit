Local OpenCV bundle for CatEditAiProSixSevenSigmaEditor.

This folder contains only the OpenCV parts required by the app:

- headers from OpenCV `core` and `imgproc`;
- generated headers for the Aurora kit/configuration;
- prebuilt `libopencv_core` and `libopencv_imgproc` libraries.

The app uses Qt to read images and OpenCV `grabCut` from `imgproc` to build the
background mask. If the Aurora kit name or OpenCV version changes, rebuild
OpenCV once and refresh this folder from the matching build output.
