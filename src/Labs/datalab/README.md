# DataLab Finish Report

## Scores

```
Correctness Results     Perf Results
Points  Rating  Errors  Points  Ops     Puzzle
1       1       0       2       7       bitXor
1       1       0       2       2       tmin
1       1       0       2       7       isTmax
2       2       0       2       7       allOddBits
2       2       0       2       2       negate
3       3       0       2       13      isAsciiDigit
3       3       0       2       8       conditional
3       3       0       2       16      isLessOrEqual
4       4       0       2       6       logicalNeg
4       4       0       2       39      howManyBits
4       4       0       2       18      floatScale2
4       4       0       2       16      floatFloat2Int
4       4       0       2       9       floatPower2

Score = 62/62 [36/36 Corr + 26/26 Perf] (150 total operators)
```

## Summary

- 使用特殊的**掩码数** `mask` 进行特定位数的遮蔽
    - 移位 & | 运算 相加数位 生成位数较大的掩码数
- 熟练使用移位操作 可以实现很多高级的运算（例如乘除法）
- `!!x` 的技巧
- 在 datalab 中使用基本位运算可以实现基本的**分支**和**条件判断**等语句
- **注意溢出问题**！有时候溢出需要额外单独处理
- `howManyBits`: 非常经典的二分
- 浮点数基本思路：**对三个部分**进行切分，对**规格化数**、**非规格化数**和**特殊数**进行三段的分类讨论
    - 浮点数同样需要考虑溢出问题！

