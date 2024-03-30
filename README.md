# AimBooster

Clicker bot for http://www.aimbooster.com. Aim Booster is a website where users click on targets that appear on the screen.

# Dependencies

- Windows (Windows api is used for clicking / screenshotting)

# The plan

- Add a way to stop the program, right now it's Alt + F4 or Ctrl + Q.
- Screenshot a specific part of the screen.
- Check for targets, use their color to find them and add them to a queue.
- Click at the targets and remove them from the queue.
- Repeat this process.

# Results

- http://www.aimbooster.com/result/8L1O47h - using template matching
- http://aimbooster.com/result/2YdJQEP - checking each pixel and clicking if it is a certain colour
- http://www.aimbooster.com/result/taTO292 - refactored the code (ended because frames reached 5fps)
