# Competitive-Programming

## Installation

1. Download MinGW installer
2. Install.
3. Run.
4. Select packages `%-base`, `%-gcc-g++`, `%-gcc-objc`
5. Apply Changes.
6. Add `~/MinGW/bin` to the system path
7. Open cmd and test if `g++` command found

## For sublime

Instruction: `sublime config` directory

## For vscode

Instruction:

1. Install `code runner` extension.
2. Go to `Preferences > Settings`.
3. Add this portion of code in the array:

``` 
"code-runner.customCommand": "cd $dir && g++ $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt<../input.txt>../output.txt"
```

4. Save.
5. Change the keyboard shortcuts for `code-runner.runCustomCommand`.
