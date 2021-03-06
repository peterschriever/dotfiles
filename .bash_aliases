alias home='cd /home/peterzen'
alias ll='ls -l'
alias la='ls -a'
alias pls=please
alias please='sudo $(fc -ln -1)'
alias shutdown='sudo shutdown 0'
alias restart='sudo restart 0'
alias python=/usr/bin/python3
alias avr-gcc-comp1='avr-gcc -g -Os -std=gnu99 -mmcu=atmega328p -c'
alias avr-gcc-comp2='avr-gcc -g -mmcu=atmega328p -o virtualglove.elf'
alias avr-gcc-comp3='avr-objcopy -j .text -j .data -O ihex virtualglove.elf'
alias django='python manage.py'
