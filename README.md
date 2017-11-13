# Ionic Cordova PNC VW Rewrite for Security APIfest 2017

_Note: requires Ionic CLI 3._

To start, run the following from inside the project directory:

```bash
npm install
```

# Creating a new page:
1. copy off any present page.
2. add this line to pages.ts replaceing 'newPageName' with your new page name.
	export const newPage = 'newPageName'

3. change the names of these files to your new page name:
	a. newPageName.html
	b. newPageName.module.ts
	c. newPageName.scss
	d. newPageName.ts
	e. folder Name

4. open newPageName.module.ts and change refrences of old page to your new page name.
	Theres 4 of them
5. in newPageName.module.ts make sure folder name './newFolderName' (line 5)
6. change 'export class oldPageModule' to a new module name

6. open scss file and change main selector to 'page-newPageName'

7. open newPage.ts change the following to your new page name:
	a. selector: 'page-oldPageName', // this is your selector from step 6
  	b. templateUrl: 'oldPageName.html'
	c. export class OldPage  

Follow these naming conventions
	a. file names are all lower case
	b. page name is camel case
	c. module name is always first letter capital camel case.

To test on a browser
```bash
ionic serve
```

to create apk
```bash
ionic cordova emulate android
```


Once APK is created, connect android phone and drag apk from this folder:
```bash
C:\Users\username\path to project\facialRec\platforms\android\build\outputs\apk
```
To the phones folder. 
Then open My Files/File Manager on the phone. 
Run the File.


# To push to git hub. https://github.com/roundpitt/facialRec.git
1. open git shell
2. cd to project
3. git add .
4. git commit -m "message here"
5. git push