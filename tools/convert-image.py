import sys
from PIL import Image

if len(sys.argv) != 2:
    print("ERROR: Invalid argument count")
    exit()

img = Image.open(sys.argv[1])

width, height = img.size

data = img.getdata()

out = open("image.bin", "wb")

converted_data = []

# Texture Dimensions
converted_data.append(img.size[0])
converted_data.append(img.size[1])

# Texture Frames
converted_data.append(1)

for i in range(len(data)):
    for j in range(0, 3):
        converted_data.append(data[i][j])

out.write(bytearray(converted_data))

out.close()