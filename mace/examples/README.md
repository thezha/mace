Examples
=======

* Build the example
```
bazel build mace/examples:helloworld \
   --crosstool_top=//external:android/crosstool \
   --host_crosstool_top=@bazel_tools//tools/cpp:toolchain \
   --cpu=armeabi-v7a
```

* To run adb inside docker, the network should use 'host':
```
docker run -it --net=host mace-dev /bin/bash
```

* Push and run the example
```
adb shell "mkdir /data/local/tmp/helloword"
adb shell push bazel-bin/mace/examples/helloworld /data/local/tmp/helloword
adb shell /data/local/tmp/helloword/helloworld
```