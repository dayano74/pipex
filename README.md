# pipex bonus part

- Handle multiple pipes.
  - This:<br>
  ```$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2```
  - Should behave like:<br>
  ```< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2```


- Support << and >> when the first parameter is "here_doc".
  - This:<br>
  ```$> ./pipex here_doc LIMITER cmd cmd1 file```
  - Should behave like:<br>
  ```cmd << LIMITER | cmd1 >> file```
