char stringToHex (String mString) {
  char myHex = 0;
  char mySplit[2];
  mString.toCharArray(mySplit, 3);

  if (mySplit[0] >= 48 and mySplit[0] <= 57) mySplit[0] = mySplit[0] - 48;
  else if (mySplit[0] >= 97 and mySplit[0] <= 102) mySplit[0] = mySplit[0] - 87;

  if (mySplit[1] >= 48 and mySplit[1] <= 57) mySplit[1] = mySplit[1] - 48;
  else if (mySplit[1] >= 97 and mySplit[1] <= 102) mySplit[1] = mySplit[1] - 87;

  myHex = ((mySplit[0] << 4) & 0xF0) | (mySplit[1] & 0x0F);

  return myHex;
}
