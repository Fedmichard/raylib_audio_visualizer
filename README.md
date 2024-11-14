# Interactive 3D Audio Visualizer
A 3D interactive audio visualizer using Raylib that dynamically transforms a mesh based on real-time audio input, creating an interactive, frequency-responsive visualization. Has added features via an interactive GUI and can be downloaded and tested by downloading the file and can be used by going into build>audio_visualizer_c.exe.

## Features
Features a 3D sphere mesh that morphs and ripples depending on the amplitude of a selected audio file in real time. Users have the option upload their own audio file in a .mp3, .ogg, .wav format and watch how it effects the sphere. There are also GUI elements which allow options for pausing and playing, effect the frequency, ripples, and intensity values applied onto the sphere, and the option to selectively change your sphere's color based on custom RGB values.

![image](https://github.com/user-attachments/assets/ee68fd48-c816-41fe-8d4a-ef077e5f3f6a)

* **Upload:** A button which allows a user to upload their own custom audio files.
* **Play:** Starts playing the audio.
* **Stop:** Pauses the audio.
* **Default:** Can be changed to "Uploaded!" or "Failed." to reflect the upload status of a user, default means the default audio is loaded in.
* **Level:** Audio Level.
* **RGB:** Color values of sphere.
* **Ripples:** How many ripples occur over the sphere.
* **Intensity:** How Intense the ripples are (how far out they go).
* **Frequency:** How frequent the waves appear.

*Used libraries/dependencies: OpenGL, RayLib, RayGUI, tinyfiledialogs, RayMath.*

## Noise Function

![image](https://github.com/user-attachments/assets/beb04364-db85-4985-a3d7-78e8b71d7296)

The noise function is very simple, it takes an xyz vertex position from our sphere mesh and a time value. The time value is automatically calculated by raylibs GetTimeFrame() function which returns an integer value that represents the time in seconds for the last drawn frame. Our Noise function returns a single float that changes based on the xyz values given, which is then put into 3 separate sinf functions which returns an oscilating value between -1 and 1 to represent a wave like shape. Inside the sinf function each vertice is multiplied by the amount of "ripples" we want in that specific direction added to the delta time multiplied by the intensity. This gives us our basic wave shape in that one direction which can then be multiplied by a frequency to get more or less waves. All the sinf functions for each subsequent vertex is then added and returned as one float value.

### Application:

![image](https://github.com/user-attachments/assets/9bf26775-0f34-4851-9ea2-80b335e7ef14)

As you can see we iterate through each vertex of our sphere mesh and since opengl is the underlying graphics api for raylib, all the shapes vertices are stored in a giant array of contiguous x, y, z values. We get a noise value based on the current x, y, z values and create a displacement variable which is multiplied to a multipier which at default is set to 1.0f. Then to maintain the shape of the sphere and keep it from extending to far off the screen or moving from it's origin we create a normalized value of x, y, z by calculating a distance from the origin and maintaining that distance. Then for each vertice we apply the displacement over the distance.

## Audio Processing Function 

![image](https://github.com/user-attachments/assets/ca44f20d-e799-4d78-8c3b-00bdaa80b1fb)

The audio processing function is used in conjunction with Raylib's AttachAudioMixedProcessor() function to allow us to add effects onto our specified audio track. It returns each sample as float values and takes a processor of type AudioCallback. The AudioCallback type takes in buffer data and frames, the buffer data just holds to current samples which will have processing applied to it and the frames or the groups of all the samples being processed at the same time, in our case our audio is processed as stereo which takes in 2 samples at a time (left and right). Samples are simply a single point of audio data, it's a snapshot of the amplitude at a given time. At the top of our application we create an averageVolume buffer which is just an array of size 400 which stores the average volume at a given moment. Then inside our function we iterate through each frame and calculate the averages. 

### Application:

![image](https://github.com/user-attachments/assets/54ce05b8-3ba4-441c-a094-b339b5f94c0f)

In our main loop we update the multiplier variable, which is 1.0f at default, by multiplying the average by 7 and adding 0.1 to it giving us a range which won't create effects to intense to where it'll deform our shape too much.

