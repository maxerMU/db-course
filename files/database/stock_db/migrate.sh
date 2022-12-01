#!/bin/bash

bash ./deploy_database.sh $1 $2 $3 $4
bash ./deploy_versions.sh $1 $2 $3 $4
bash ./deploy_procedures.sh $1 $2 $3 $4
bash ./deploy_functions.sh $1 $2 $3 $4