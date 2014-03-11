#version 120

attribute vec2 position;

void main()
{
  gl_Position.xy = position;
  gl_Position.z = 1.0;
}
