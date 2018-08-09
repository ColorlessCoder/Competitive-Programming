# Competitive-Programming

## For sublime

Instruction: `sublime config` directory

## For vscode

Instruction:

1. Install `code runner` extension.
2. Go to `Preferences > Settings`.
3. Add this portion of code in the array:

``` "code-runner.customCommand": "cd $dir && g++ $fileName -o $fileNameWithoutExt &&      $dir$fileNameWithoutExt<../input.txt>../output.txt"
```

4. Save.
5. Change the keyboard shortcuts for `code-runner.runCustomCommand`.