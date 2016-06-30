inline float convolveBridgeIR(float input)
{
  static const int irlength = 2048;
  static const float ir[irlength] = {/*insert IR here*/};
  static float buffer[irlength];
  
  static int count = 0;
  
  const float *impulsePos = ir;
  float *bufferPos = buffer;

  const float *endImpulse = ir + irlength;
  float *endBuffer = buffer + irlength;

  float outputSample;

  *( bufferPos += count ) = input;

  outputSample = *impulsePos++ * *bufferPos++;

  while (bufferPos < endBuffer)
  {
    outputSample += *impulsePos++ * *bufferPos++;
  }

  bufferPos -= irlength;

  while (impulsePos < endImpulse)
  {
    outputSample += *impulsePos++ * *bufferPos++;
  }

  if ((count -= 1) < 0)
  {
    count = irlength -1;
  }

  return outputSample;
}