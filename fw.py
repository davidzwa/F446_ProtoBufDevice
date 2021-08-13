from shutil import copyfile

src = "C:\\Users\\david\\Projects\\ARM\\Tomato_Software\\build\\src\\apps\\ping-pong\\ping-pong.bin"

dst = "E:\\ping-pong.bin"
copyfile(src, dst)

# dst2 = "F:\\ping-pong.bin"
# copyfile(src, dst2)