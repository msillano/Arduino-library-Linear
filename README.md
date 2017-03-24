# Arduino-library-Linear
Extends the Smooth library doing a linear conversion of readings.

This library transforms mV (as from Smooth) to fisical units using a linear equation: y = m*x + q:
-   x = the avg mV value
-   y = the fisical value
-   m = default 1.0 (scale factor)
-   q = default 0.0 (offset)

Allow interactive tarature.
- Uses Smooth lib: https://github.com/msillano/Arduino-library-smooth
