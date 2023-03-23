# Deeper is Better
Official write-up for a challenge in NasCon CTF '23

## Challenge
<b>Name</b><br/>
Deeper is Better<br/><br/>
<b>Description</b><br/>
Someone messed up my program in a way that even I can't understand. Put the pieces together to find the flag.
<br/><br/>
<b>Hints</b><br/>
- Nine is the magic number
- Remember that lesson your fornesics teacher gave you?<br/><br/>

<b>File</b><br/>
[Deeps](./deeps)

## Solve 
### String search
Since this is a reverse engineering challenge, we will first be looking for strings in the file. We go ahead and run the command ```strings deeps```. <br/>
![image](https://user-images.githubusercontent.com/88616338/227126951-6f640759-7c6c-4b6c-a46b-01e1a2940372.png)<br/>
We get these weird chunks of data that look like base 64 encoded strings. We go to [CyberChef](gchq.github.io/CyberChef) and we find a few interesting strings. However, this is not enough.

### Running
Since string search does not help us a lot, we go ahead and run the program.<br/>
![image](https://user-images.githubusercontent.com/88616338/227128975-9f715ebc-22c7-4be8-ae5a-00ba8f8b133a.png)
<br/>What is this? We get a statement saying <i>You're a loser if you can't go deep</i>. I think that is a hint but it doesn't help us a lot right now. The program asks us input so we just provide a random input such as ```hello```, and we get what looks like a base 64 encoded string! Let's check out what that is.<br/>
![image](https://user-images.githubusercontent.com/88616338/227129682-a41eb096-5a41-44de-b0b5-dd844a6f1c8c.png)
<br/>What??? Well, that looks like a rabbit hole, so we can go ahead and disassemble the binary now :(

### Disassembly
We go ahead and disassemble the executable in [Ghidra](https://ghidra-sre.org/) and...<br/>
![image](https://user-images.githubusercontent.com/88616338/227131092-d21dbea4-742a-4ace-be75-e3826c508726.png)<br/>...these are all the functions. Is it weird functions are starting from "one" and going till "twenty"? Let's see. We start looking at the code of each function in Decompiler view.
#### main
The main function just takes an input and calls the function "one"<br/>
![image](https://user-images.githubusercontent.com/88616338/227132963-3bd7ffef-92d5-461c-9307-13ec414dddfd.png)
<br/>
#### one
It looks like a string, stored as as long integers, is being printed. <br/>
![image](https://user-images.githubusercontent.com/88616338/227133324-582c132f-a3c7-4e0c-b492-79548345846f.png)
<br/>We convert the bytes before the null byte, from little endian to big endian, and then to a string and we get a base64 string. Let's decode it. <br/>
![image](https://user-images.githubusercontent.com/88616338/227133486-803ecc4f-19f4-42e0-a02c-b8e5f71c1041.png)
<br/>Another rabbit hole :(
#### Giving up 😂
Now, either we can search each function manually and get a rabbit hole in most of them, or we can look at the first hint. The hint says "<i>Nine is the magic number</i>". Does it mean the function "nine"? Idk, let's see...
#### nine
We go ahead and look at function "nine". There appears to be some dead code for obfuscation. However there is a string being printed too, like all the other functions. It's a base64 encoded string. Let's go ahead and decode this one...<br/>
![image](https://user-images.githubusercontent.com/88616338/227135579-0287cccd-d9e8-441a-8c5f-78151dd0cdd5.png)
<br/>Could this be the flag? We try submitting it and it doesn't work. For 250 points, I didn't have many hopes either. Maybe this is part of the flag? We keep this in our notes and move on. 
<br/><br/>
Unfortunately, none of the other 19 functions contain any meaningful strings. What could it be? There must be another way to look for the rest of the flag. 

### The other way
We go ahead and take up the second hint, "<i>Remember that lesson your forensics teacher gave you?</i>" and takes some time for us to realise this but maybe there is some forensics involved in this challenge. We've already checked the strings and there was nothing useful there. There was, however, that one statement: "<i>You're a loser if you can't go deep</i>". Could there be a hidden file, maybe?<br/>
#### Looking for hidden files
To look for (and extract) hidden files within files, we can [Binwalk](https://github.com/ReFirmLabs/binwalk). We go ahead and use the command ```binwalk -e deeps``` to look for and extract any hidden files within the executable.<br/>
![image](https://user-images.githubusercontent.com/88616338/227137535-147d1b1e-1c60-4a9b-bb86-936a64e60829.png)
<br/>
It looks like a zip, containing an ELF, has been found within the executable. Let's go ahead and look at this file.<br/>
![image](https://user-images.githubusercontent.com/88616338/227137880-6bb2fedf-28f6-4f73-ad5a-c064780d06b0.png)
<br/>That's nice. At least we're going the right way.
