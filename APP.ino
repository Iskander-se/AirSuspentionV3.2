void GetLevelInstance (byte addr) {
  //if (addr > 0)GetLevelPreset(addr);
  IntentHeap.curTargetLevels[0] = cStatus.PresetLevels[0] * 10 + cStatus.shiftL;
  IntentHeap.curTargetLevels[1] = cStatus.PresetLevels[0] * 10 + cStatus.shiftR;
  IntentHeap.curTargetLevels[2] = cStatus.PresetLevels[1] * 10 + cStatus.shiftL;
  IntentHeap.curTargetLevels[3] = cStatus.PresetLevels[1] * 10 + cStatus.shiftR;

}
