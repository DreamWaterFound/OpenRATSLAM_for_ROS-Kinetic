# OpenRatSLAM for ROS (Kinetic)

This is a version of Open_RAT-SLAM for ROS Kinetic with little codes modified to overcome the problem of Irrlicht. 

## Why this repository existed

Reason is simple : I have to waste many time on making it working!  (Maybe it's easy for you)

OpenRatSLAM is the implementation of an interesting idea and attracted me. However OpenRatSLAM only tested in Ubuntu 12.04, while it seems doesn't work well under Ubuntu 16.04 with ROS Kinetic which I was used. So I spend several days to solve problems one by one. Finally I think it is necessary to create a repository to record changes and help someone like you to save time.

The original version of this program is [here](https://github.com/davidmball/ratslam).

## Dependencies

OpenRatSLAM has it's dependices:

- ROS 
 
   Robotic Operating System. The distro version this repository needs is Kinetic. May other distro version can also work well.

- OpenCV
   
   A computer vision library. I just tested OpenRatSLAM on 3.3.1 and it can works well.

- Irrlicht

    A 3D engine for games. I tested on 1.6.1 and it works well. By the way I found that it can't work with the irrlicht library's version lower than 1.6.0.

    You can download it [here](https://sourceforge.net/projects/irrlicht/files/Irrlicht%20SDK/).

- Your patience

    ; ) 

## Build

1. Make sure you have install irrlicht correctly. You may need to create a folder neamed "irrlicht" under the "include" folder and put all the header files in it, like this:
   
    (irrlicht root)

    &nbsp;&nbsp;&nbsp;&nbsp;├── include

    &nbsp;&nbsp;&nbsp;&nbsp;│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── irrlicht

    &nbsp;&nbsp;&nbsp;&nbsp;│&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── (header files)

    &nbsp;&nbsp;&nbsp;&nbsp;└── lib

    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;└── libIrrlicht.a

    In addition, in order to let cmake can find irrlicht, remember to add an environment variable named IRRDIR which stored it's root path. You can add the following line in ~/.bashrc:

    `export IRRDIR="Your irrlicht library root path"`

    If you are familiar with cmake, you can also add your library path to CMakelIsts.txt or FindIrrlicht.cmake. 

2. Make a folder in catkin workspace and git this repository.

3. Run "catkin_make" in catkin workspace.

4. Start roscore and play bag file, for example :
   
   `rosbag play ~/Datasets/irat_aus_28112011.bag `

5. Start up OpenRatSLAM and enjoy.

    `roslaunch ratslam_ros irataus.launch`

6. **Notes** : If you installed anaconda or pyenv, it's recommand to disable it. These two tools will make some mysterious problems during OpenRatSLAM running, which I have not been solved yet. I am welcome to share with me If you find a solution.
   
## Different from the original code

All the codes I modified were marked in the files and it looks like:

```
/* ==============================↓↓↓↓↓==== [deleted] ====↓↓↓↓↓===================================
...
   ==============================↑↑↑↑↑==== [deleted] ====↑↑↑↑↑=================================== */
```

or

```
// ===============================↓↓↓↓↓==== [added] ====↓↓↓↓↓====================================
...
// ===============================↑↑↑↑↑==== [added] ====↑↑↑↑↑====================================
```

Only two files were modified : [CMakeLists.txt](https://github.com/DreamWaterFound/OpenRATSLAM_for_ROS-Kinetic/blob/master/CMakeLists.txt) and [/src/graphics/local_view_scence.h](https://github.com/DreamWaterFound/OpenRATSLAM_for_ROS-Kinetic/blob/master/src/graphics/local_view_scene.h) . 

In [CMakeLists.txt](https://github.com/DreamWaterFound/OpenRATSLAM_for_ROS-Kinetic/blob/master/CMakeLists.txt) I add some code to support irrclicht completely. In [/src/graphics/local_view_scence.h](https://github.com/DreamWaterFound/OpenRATSLAM_for_ROS-Kinetic/blob/master/src/graphics/local_view_scene.h) , I deleted codes about irrclicht, and added a simple image viewer using OpenCV. I found that irrclicht operation in  [/src/graphics/local_view_scence.h](https://github.com/DreamWaterFound/OpenRATSLAM_for_ROS-Kinetic/blob/master/src/graphics/local_view_scene.h) will cause the callback function which  cannot be called. 

## More


I hope this little work can help you.

If you have better solutions to the problems that arise, please create an issue and share with me. ; )

The following is the ReadMe.md of [original repository](https://github.com/davidmball/ratslam).

----


<img src='https://wiki.qut.edu.au/download/attachments/104094381/logo_sml.jpg?version=1&modificationDate=1338441816000'>

<b>RatSLAM</b> is a bio-inspired simultaneous localisation and mapping (SLAM) system. Based on continous attractor network dynamics, RatSLAM is capable of mapping by closing loops to correct odometry error.<br>
<br>
The original RatSLAM algorithm was designed and implemented on Pioneer robots by Michael Milford and Gordon Wyeth (see <a href='http://eprints.qut.edu.au/37593/1/c37593.pdf'>RatSLAM: a hippocampal model for simultaneous localization and mapping</a>).<br>
<br>
There is an openRatSLAM paper available in <a href='http://www.springerlink.com/openurl.asp?genre=article&id=doi:10.1007/s10514-012-9317-9'>Autonomous Robots</a>. This paper describes how openRatSLAM works in technical detail.  If you use the code we would appreciate cites please.<br>
<br>
The C++ RatSLAM implementation is currently being used to power the iRat robot when it is <a href='http://ratslam.itee.uq.edu.au/live.html'>online</a> and in recent ports of the <a href='http://itee.uq.edu.au/~ruth/Lingodroids.htm'>Lingodroids project</a> to use the iRat.<br>
<br>
There are now two versions of RatSLAM available, both based on the same code:<br>
<ul><li><b>(NEW)</b> <a href='https://github.com/davidmball/ratslam/blob/wiki/RatSLAMROS.md'>A ROS-based version</a>
</li><li><a href='https://github.com/davidmball/ratslam/blob/wiki/RatSLAMLibrary.md'>A C++ library</a></li></ul>

We provide three datasets for the ROS version of openRatSLAM available at <a href='https://wiki.qut.edu.au/display/cyphy/openRatSLAM+datasets'>QUT cyphy</a> for:<br>
<ul><li>iRat in an Australian set (2011)<br>
</li><li>Car in St Lucia suburb (2007)<br>
</li><li>Oxford's New College (2008)</li></ul>

The code is released under the GNU GPL V3. Please contact David Ball if you require a more permissive license.
