feh --bg-scale /home/nikolas/wallpapers/1.jpg
urxvt256cd -f -q -o &
while true; do
	#battery_info=`acpi -b`
	#battery_status=`grep
    volume=`amixer sget Master | grep -oP '(\d{1,})%'`
	battery_status=`acpi -b | grep -oP '(\d{1,})%'`
	current_date=`date +'%D %R'`
	result="][ $battery_status ][ $current_date ]"
	xsetroot -name "$result"
	sleep 1m
done &
exec dwm-start

