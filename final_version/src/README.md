[BUILDING]

CAUTION: MAC ONLY

Please properly install Eigen and NLOpt as outlined in external.pdf.
In final_version/,
	mkdir build
	cd build
	cmake ../src

Then the built final_version executable can be found at:
	build/assemble/final_version

[TESTING]

We have provided a png file "horse.png" and you can use it to test our program.
Just copy the file and put it under :
	build/assemble/
The size of photo is limited to 500x500 if you want to use your own photo.
Also, we have provided a compiled final_versoin.app file in final_version/src, just in case.
    
[HOW TO USE]

After launching the program, use the open button on the toolbar on top of the screen to import the png file.
Then drag the slider bar and stop at the position where (you think) the shown image is the best.
Click next.
Drag the slider bar again and stop at the position where the shown image is the best.
Repeat the above process until you are totally satisfied with the image.
