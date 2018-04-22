[BUILDING]

CAUTION: MAC ONLY

Please properly install Eigen and NLOpt as outlined in external.pdf.
In alpha_version/,
	mkdir build
	cd build
	cmake ../src

Then the built alpha_version executable can be found at:
	build/assemble/alpha_version


[TESTING]

We have provided a png file "incline_L.png" and you can use it to test our program.
Just copy the file and put it under :
	build/assemble/

After launching the program, use the open button on the toolbar on top of the screen to import the png file.
Then drag the slider bar and stop at the position where (you think) the shown image is the best.
Click next.
Drag the slider bar again and stop at the position where the shown image is the best.
Repeat the above process until you are totally satisfied with the image.

[TO DO for SimpleLazyTeam]

Right now, in this alpha-version,
1. The optimization process is just random calculations.
   It will be replaced when that portion is done.
2. The image is just filtered by a single curve filter.
   The curve filter will be replaced with 6 different filters once they are implemented.
   Then the image would be filtered by all 6 filters simultaneously.
3. The export button is there but it has no function yet.
   It will be implemented and allow the users to save their results.
4. Our program can only build for MAC right now.
   This is because we haven't figured out how to install NLOpt on other platforms.
   We will resolve this program and get our program working cross-platform soon.
