# Operating Systems Practical Exercise 2

## Documentation for task e)

'An explanation is enough – fixing the problem can be quite a bit of work, depending on the approach…' - Michael Engel

**Description of the task**
As implemented, the web server has a significant security problem: it allows not only to access files under the www-path directory, but enables access to all files in the file system of the server that can be accessed by the user who started the webserver process.
Find a way to exploit this security problem. Then, find two different ways to prevent access to files outside of the webroot directory.

Litt vanskelig å få dette ned på engelsk, men kort svar på spm om å passe på at man ikke får tilgang til alle filene på pc:

1. If you like to make sure that files that is outside the web root directory are not accessible, you have to make sure that the directory is restricted with “Allow” and “Deny option” in your web server configuration file. (direkte kopiert fra https://www.wikitechy.com/tutorials/apache/restricting-access-to-files-outside-the-web-root-directory)

2. Passe på dette med .. i pathen. Hvis vi har dette så betyr det at man beveger seg ut av mapper som er ugunstig mtp å få tilgang til mappene utenfor, og evt alle andre mapper
