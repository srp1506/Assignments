.section .data

L1:.word 1000000 # Delay for the LED
L2:.word 0x10012000 # Address concerning the Sparkfun RED-V Redboard initialisation and control

.section .text
.global main

main:

la x3, L1
lw x3, 0(x3) # Loading delay value
la x2, L2
lw x2, 0(x2) # Loading address
addi x1, x0, 32 # Loading 'turn on' variable
addi x5, x0, 0 # Initialising the delay control variable
sw x0, 4(x2) #Initialising the Sparkfun RED-V Redboard
sw x1, 8(x2) #Initialising the Sparkfun RED-V Redboard

On: # Turns the LED on
    addi x5, x0, 0 # Reinitialising the delay control variable
    sw x1, 12(x2) # Turning LED on

    On_delay: # Delays the code from entering the off sequence
        beq x5, x3, Off # Once delay cycle is over redirects to off sequence
        addi x5, x5, 1
        beq x0, x0, On_delay # Loops the delay sequence based on the delay value

Off: # Turns the LED off
    addi x5, x0, 0 # Reinitialising the delay control variable
    sw x0, 12(x2) # Turning LED off

    Off_delay: # Delays the code from entering the on sequence
        beq x5, x3, On # Once delay cycle is over redirects to on sequence
        addi x5, x5, 1
        beq x0, x0, Off_delay # Loops the delay sequence based on the delay value
        
# Submission By : Soham Rajesh Pawar and Siddhant Sanjay Godbole