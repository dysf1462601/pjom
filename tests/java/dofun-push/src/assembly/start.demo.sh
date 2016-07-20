#! /bin/bash
DEPLOY_DIR='/pom/java'

cd $DEPLOY_DIR

svn update

pid=$(ps -ef | grep "dofun-" | grep -v grep | awk '{print $2}')
echo $pid
if [ ! -n "$pid" ]; then
	echo "dofun Service NOT RESTART!"
else
	kill -9 $pid
fi

LIB_DIR=$DEPLOY_DIR/dofun-sys/target/lib
LIB_JARS=`ls $LIB_DIR|grep .jar|awk '{print "'$LIB_DIR'/"$0}'|tr "\n" ":"`

CONF_DIR=$DEPLOY_DIR/dofun-sys/target/classes/
CP=$CONF_DIR:$LIB_JARS

sudo java -classpath $CP com.dofun.SysApplicationServer > /dev/null 2>&1 &

LIB_DIR=$DEPLOY_DIR/dofun-uc/target/lib
LIB_JARS=`ls $LIB_DIR|grep .jar|awk '{print "'$LIB_DIR'/"$0}'|tr "\n" ":"`
CONF_DIR=$DEPLOY_DIR/dofun-uc/target/classes/
CP=$CONF_DIR:$LIB_JARS
sudo java -classpath $CP com.dofun.UcApplicationServer > /dev/null 2>&1 &



LIB_DIR=$DEPLOY_DIR/dofun-car/target/lib
LIB_JARS=`ls $LIB_DIR|grep .jar|awk '{print "'$LIB_DIR'/"$0}'|tr "\n" ":"`
CONF_DIR=$DEPLOY_DIR/dofun-car/target/classes/
CP=$CONF_DIR:$LIB_JARS
sudo java -classpath $CP com.dofun.CarApplicationServer > /dev/null 2>&1 &


LIB_DIR=$DEPLOY_DIR/dofun-app/target/lib
LIB_JARS=`ls $LIB_DIR|grep .jar|awk '{print "'$LIB_DIR'/"$0}'|tr "\n" ":"`
CONF_DIR=$DEPLOY_DIR/dofun-app/target/classes/
CP=$CONF_DIR:$LIB_JARS
sudo java -classpath $CP com.dofun.AppApplicationServer > /dev/null 2>&1 &
