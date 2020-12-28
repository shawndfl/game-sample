# game-sample

This is a sample game with opengl es graphics

#Setup

```Bash
sudo apt install  libglfw3-dev libpng-dev
```

# Build 

```
make -j 10
```

# Run 

```
./BlockSimulatedKingdom
```

# TODO
* [ ] Add movement to the character when the user hits `left` and `right` key.
* [ ] Make character jump with `space` key.
* [x] Finish making materials to display textures
* [_] Add Vector3 math and unit tests.
* [x] Read input from the keyboard.
* [x] Get text to display.
* [x] Get controller input working.
* [x] Add some sample character animation to single texture. Each frame is 32x32.
* [x] Update the `ShaderSprite` to allow textures to scale and have an offset. 
