# subshifter
so this torrent of "ashes of time" by wong kar-wai i had downloaded had a portugese sub file and an english sub file

now the english one had the stime stamps all messed up, like they started at 1h 30 minutes and i couldn't bother trying to fix it in mpv so i decided to write a computer program that would scrape the correct time stamps off the portugese file and slam them on the english file

now the problem is that i do not know how to write computer programs and i had decided that i wouldn't use the internet that day (had had a shitty week at work and needed to wind down) so i couldn't just copy paste stuff from stackexchange

(seriously, given a pen and paper i couldn't write a hello world that compiles, that's how bad i am at writing computer programs)

luckily i had a copy of my bachelors thesis code on my laptop, and i managed to make a fork of this quantum chemistry program that now also fixes messed up subtitle files

removing any part of the quantum chemistry stuff would make the program not compile (i do not know how to use make) so umm yeah it's a big mess but it works i guess
# usage
running
'./main subshift file-with-good-time-stamps file-with-bad-time-stamps'
overwrites the srt file with the bad time stamps with the good time stamps
# note to future employers

