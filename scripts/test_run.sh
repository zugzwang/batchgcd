#!/bin/bash

toy_moduli=testdata/toy.moduli
toy_moduli_10=testdata/toy-base10.moduli

echo "This will run batchGCD on a tiny set of moduli:"
cat $toy_moduli
read -p "Press enter to continue "; echo ""
make batchgcd
./batchgcd $toy_moduli
read -p "Press enter to continue "; echo ""

echo "Now with the the same moduli, base 10:"
cat $toy_moduli_10
read -p "Press enter to continue"
./batchgcd $toy_moduli_10 -base10
