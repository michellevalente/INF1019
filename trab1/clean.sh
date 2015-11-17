#!/bin/bash
set -u
set -e

silent=true
OPTIND=1
while getopts ":v" OPT; do
    case $OPT in
        v) silent=false ;;
        [?])
            echo "Unknown option -$OPTARG" >&2
            printusage
            exit 1
        ;;
        :)
            echo "Option -$OPTARG requires an argument" >&2
            printusage
            exit 1
        ;;
    esac
done
while [ $OPTIND -gt 1 ]; do let OPTIND--; shift; done

shm_users=()
shm_count=()

while read key id owner nattch; do
	if [ -z "$key" ] || [ -z "$id" ] || [ -z "$owner" ]; then
		echo "Invalid line from ipcs: \"${key} ${id} ${owner} ${nattch}\"!" >&2
		exit 1
	fi
	
	if ! output=$(ipcrm shm $id 2>&1); then
		echo "Failed to delete line from ipcs: \"${key} ${id} ${owner} ${nattch}\"!" >&2
		echo "Output given: \"${output}\"" >&2
		exit 1
	fi
	
	found=false
	i=0
	if [ -n "${shm_users[*]:-}" ]; then
		for user in "${shm_users[@]}"; do
			if [[ "$user" == "$owner" ]]; then
				shm_count[$i]=$(( ${shm_count[$i]} + 1 ))
				continue 2
			fi
			let i+=1
		done
	fi

	shm_users[${#shm_users[*]:-0}]=${owner}
	shm_count[${#shm_count[*]:-0}]=1
done < <(ipcs -m | grep "^0x" | awk '{print $1, $2, $3, $6}' | grep " 0$")

if [ -z "${shm_users[*]:-}" ]; then
	$silent || echo "No unattached SHM segments found."
	exit 0
fi

total=0
echo "Removed SHM Segments:"
echo "___________________________"
echo "|   OWNER    |   COUNT    |"
echo "|------------|------------|"
for i in $(seq 0 $(( ${#shm_users[*]} - 1 ))); do
	printf "| %-10s | %10d |\n" "${shm_users[$i]}" "${shm_count[$i]}"
	let total+=${shm_count[$i]}
done
echo "|____________|____________|"
echo
echo "Total: $total"
