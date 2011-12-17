#!/usr/bin/env python
#
# name:      pcc_numpy.py
# author:    QIAO Nan <qiaonancn@gmail.com>
# license:   GPL
# created:   2011 Dec 17
# modified:  2011 Dec 17
#
import numpy as np
a=[1,2,3,4,5]
b=[2,2,3,4,6]
print a, b, np.corrcoef(a, b)
