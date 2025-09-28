# PROTOCOL DRAFT

```
 0      7 8    12   16   20   
+--------+----+----+----+----+
| PT 0x01| N1 | O1 | N2 | O2 |
+--------+----+----+----+----+

 0      7 8      X
+--------+--------+
| PT 0x8.|  NAME  |
+--------+--------+

 0      7 8     15
+--------+--------+
| PT 0x9.|  CGRD  |
+--------+--------+
```

## PT - Packet Type
* 0x01: Interval Challenge
* 0x80: Assigned Name (self)
* 0x81-8F: Assigned Name (Player 1-17)
* 0x90: Current Grade (self)
* 0x91-9F: Current Grade (Player 1-17)

## N - Note
* 0x1 - 0xC: C,C♯,D,D♯,E,F,F♯,G,G♯,A,A♯,H

## O - Octave
* 0x0 - 0x8: Octave 0-8

## NAME - Name
* 0x\*: UTF-8 Name

## CGRD - Current Grade
* 0x00-64: Current Grade from 0-100
