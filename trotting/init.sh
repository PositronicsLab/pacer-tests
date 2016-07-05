#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
pushd .
cd ${DIR}


../setup-tests.sh *.in ;

legMult=$(python -c "import random;print(random.uniform(0.1, .9))")
legMult=$(echo "scale=2;$legMult" | bc)

legFMult=$(python -c "import random;print(random.uniform(0.1, .9))")
legFMult=$(echo "scale=2;$legFMult" | bc)

legHMult=$(python -c "import random;print(random.uniform(0.1, .9))")
legHMult=$(echo "scale=2;$legHMult" | bc)

denseMult=$(python -c "import random;print(random.uniform(1, 6))")
denseMult=$(echo "scale=2;$denseMult" | bc)

lenTotal=.194
lenFTot=$(echo "scale=2;$lenTotal*$legMult" | bc)
lenHTot=$(echo "scale=2;$lenTotal-$lenFTot" | bc)

export lenF1=$(echo "scale=2;$lenFTot*$legFMult" | bc)
export lenF2=$(echo "scale=2;$lenFTot-$lenF1" | bc)

export lenH1=$(echo "scale=2;$lenHTot*$legHMult" | bc)
export lenH2=$(echo "scale=2;$lenHTot-$lenH1" | bc)

export base_size_length=$(python -c "import random;print(random.uniform(0.05, 0.3))")
export base_size_width=$(python -c "import random;print(random.uniform(0.01, 0.2))")
export base_size_height=$(python -c "import random;print(random.uniform(0.01, 0.05))")

export density=$(echo "scale=2;1000*$denseMult" | bc)

#echo "$lenF1 $lenF2 $lenH1 $lenH2 $density $base_size_length $base_size_width $base_size_height"  >> matlabData.txt;

printf "%s" "$lenF1 $lenF2 $lenH1 $lenH2 $density $base_size_length $base_size_width $base_size_height"  >> matlabData.txt; 

popd
