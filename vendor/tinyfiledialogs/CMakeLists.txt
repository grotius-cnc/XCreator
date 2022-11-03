cmake_minimum_required(VERSION 2.6)
project(tinyfd)

ADD_LIBRARY(tinyfd STATIC
  tinyfiledialogs.cpp
  tinyfd_moredialogs.cpp
  )
