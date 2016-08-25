from distutils.core import setup, Extension

module = Extension("pypersonality", sources = ["pypersonality.c"])

setup(name="PersonalityPackage",
	  version="1.0", 
	  description="Package for personality",
	  ext_modules=[module])
	  
