
echo "Write name of assignment"
read assignment

echo "enter deadline"
read Deadline

current_date=$(date +"%Y-%m-%d")
line_one="Assignment: $assignment pending on $current_date"
line_two="Deadline: $Deadline"


for file in *.txt; 
    do
    
        if [ -f "$file" ]; then
       
            echo "$line_one" >> "$file"
            echo "$line_two">>"$file"
            echo "--------------">>"$file"
            students_exist=true
        fi
    done

if [ "$students_exist" = true ]; then
    echo "Added assignment successfully."
else
    echo "No student files found to add the assignment."
fi

