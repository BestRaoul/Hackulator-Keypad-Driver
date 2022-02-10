# PI30-w keypad driver
PI30-w keypad driver

An adaptation of the hackulator keypad driver to make it work with my ti30 eco
and some preferences changes.

Main changes:
  5x8 matrix
  keys layouts have been modified (letters, symbols & numbers, game, ...)

#Dependencies

```
sudo apt-get install libgtk2.0-dev cmake xorg openbox libxt-dev libxtst-dev

cd /tmp
wget https://project-downloads.drogon.net/wiringpi-latest.deb
sudo dpkg -i wiringpi-latest.deb
rm wiringpi-latest.deb
```
