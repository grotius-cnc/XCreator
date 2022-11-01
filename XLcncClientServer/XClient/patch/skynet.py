print("python module skynet cyberdyne loaded.")
from ctypes import * # cdll
import OpenGL.GL as gl # also added in the axis.py file.

lib = cdll.LoadLibrary('/home/user/XCreator/XLcncClientServer/build/XClient/libXClient.so')

# create a binding class to c++.
class XClient(object):

    # constructor
    def __init__(self):

        # attribute
        self.obj = lib.XClient_new()

    # define method
    def run(self):
        lib.XClient_run(self.obj)

    # define method
    def encodeRawToPng(self,pixels,w,h):
        lib.XClient_encodeRawToPng(self.obj,pixels,w,h)

# create a XClient class object
f = XClient()

# Create image from openGl.
def get_image(self):
        """
        Read the openGl backbuffer just before bufferswap is done.
        """
        w = self.winfo_width()
        h = self.winfo_height()
        gl.glReadBuffer(gl.GL_BACK)

        pixels=(gl.GLbyte*(w*h*4))()
        pixels=gl.glReadPixels(0, 0, w,h, gl.GL_RGBA, gl.GL_UNSIGNED_BYTE)

        # 4 channel rgba input.
        f.encodeRawToPng(pixels,w,h)
        f.run()

# Example:
# set data types of arguments of cpp function
# lib.isNExist.argtypes = [c_char_p]
# set result data type
# lib.isNExist.restype = c_int
# string I want to pass to the function
# s = "Hello world!".encode("UTF-8")
# create buffer that will pass my string to cpp function
# buff = create_string_buffer(s)
# passing buff to function
# result = lib.isNExist(buff)


