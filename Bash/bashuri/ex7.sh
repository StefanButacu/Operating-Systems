#!/bin/bash
# gasiti recursiv intr un director toate legaturile simbolic si raportati care dintre ele sunt legate de fisiere directoare care nu exista . test -L pt a verifica daca un string este link symbolic si -e ca sa verificam daca e valid 

for file in $(find "$1" -type l); do
	if [ ! -e "$file" ]; then
		echo "Link invalid $file"
	fi
done	
