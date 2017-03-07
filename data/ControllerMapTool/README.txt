SDL has two game controller modes on Windows: XInput and DirectInput.
XInput is newer and more compatible but only supports 4 controllers.  This is the default mode.

You can switch to DirectInput in the controller options if you want to play with lots of players.
In that case, it is possible that your controller will not be detected properly.

Try running DirectInputControllerMap.bat with only the non-working controller plugged in. (Or, if you are trying to use XInput and it doesn't work, use XInputControllerMap.bat)
This will generate a controller description string which you can append to the bottom of data/gamecontrollerdb.txt.  This should make your controller work, hopefully!

You should also email it to bugs@bobsgame.com so that I can add it to the official build.
I will also try to add it to the official GameControllerDB project on GitHub so that it will help fix other games as well!