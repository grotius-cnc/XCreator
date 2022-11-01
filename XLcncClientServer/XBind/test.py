import OpenGL.GL as gl # also added in the axis.py file.
# import the module
from ctypes import *
# load the library
lib = cdll.LoadLibrary('./build/libXBind.so')

# create a binding class to c++.
class XClient(object):

    # constructor
    def __init__(self):

        # attribute
        self.obj = lib.XClient_new()

    # define method
    def test(self, arg):
        print(arg)

    # define method
    def printStatus(self):
        lib.XClient_printStatus(self.obj)

    # define method
    def testExtern(self,arg):
        lib.XClient_test(self.obj,arg)

    # define method
    def setData(self,pixels,width,height,channels):
        lib.XClient_setData(self.obj,pixels,width,height,channels)

# create a XClient class object
f = XClient()

# Create image from openGl.
def get_image(self):
        print("python module active.")
        """
        Read the openGl backbuffer just before bufferswap is done.
        """
        w = self.winfo_width()
        h = self.winfo_height()
        gl.glReadBuffer(gl.GL_BACK)

        pixels=(gl.GLubyte * (4*w*h))(0)
        gl.glReadPixels(0, 0, w,h, gl.GL_RGBA, gl.GL_UNSIGNED_BYTE,pixels)

        # string I want to pass to the function
        msg = "Test message from skynet.py".encode("UTF-8")
        # create buffer that will pass my string to cpp function
        strBuffer = create_string_buffer(msg)
        f.testExtern(strBuffer)

        f.setData(pixels,w,h,4)

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
