#!/bin/bash
# @copyright Copyright 2011 City of Bloomington, Indiana
# @license http://www.gnu.org/copyleft/gpl.html GNU/GPL, see LICENSE.txt
# @author Cliff Ingham <inghamn@bloomington.in.gov>
#
# Creates a tarball containing a full snapshot of the data in the site
MONGODUMP=/usr/local/mongo/bin/mongodump
MONGO_DB=crm
BACKUP_DIR=/var/www/backups/crm

# How many days worth of tarballs to keep around
num_days_to_keep=5

#----------------------------------------------------------
# No Editing Required below this line
#----------------------------------------------------------
now=`date +%s`
today=`date +%F`

cd $BACKUP_DIR

# Dump the database
$MONGODUMP -d $MONGO_DB -o $today

# Tarball the Data
tar czf $today.tar.gz $today
rm -Rf $today

# Purge any backup tarballs that are too old
for file in `ls`
do
	atime=`stat -c %Y $file`
	if [ $(( $now - $atime >= $num_days_to_keep*24*60*60 )) = 1 ]
	then
		rm $file
	fi
done
