import Felgo 3.0
import QtQuick 2.0
import QtCharts 2.3

FlickablePage {
    scrollIndicator.visible: true
    flickable.contentHeight: column.height

    Column{
        id: column
        anchors.centerIn: parent
        InfoLabel{
            id: mostPlayedNote
            fieldName: "Nota más tocada: "
            property var notesPlayed : [];
            function addNote(note){
                let noteAcc = notesPlayed.filter(v => v.note === note);

                if(noteAcc.length === 0){
                    notesPlayed.push({note: note, count: 0});
                }else{
                    noteAcc[0].count++;
                }

                let mostPlayed = notesPlayed.reduce(
                       (previous,current) => (previous.count > current.count) ? previous : current,
                       {note: 0, count: 0});

                change(mostPlayed.note);
                notesChart.generateChart(notesPlayed)
            }
        }

        ChartView{
            height: dp(250)
            width: Math.min( dp(700), parent.parent.width * 0.8)
            legend.visible: true
            antialiasing: true
            //animationOptions: ChartView.AllAnimations

            PieSeries{
                id: notesChart
                holeSize: 0.25

                function generateChart(data){
                    data.forEach(e => {

                        if(e.note === 0)
                            return;

                        var slice = find(e.note);

                        if(slice === null){
                            append(e.note,e.count).labelVisible = true;
                        }else{
                            slice.value = e.count;
                        }

                    });
                }
            }
        }

        InfoLabel{
            id: volumeAverage
            fieldName: "Volumen usual: "
            property var maxValues : 10000
            property var values : []
            property var avgData : ({sum: 0, count: 0});
            function addValue(value){
                values.push(value);

                if(values.length > maxValues)
                    values.shift();

                change(Math.floor( values.reduce( (acc, val) => acc + val ) / values.length ));
            }
        }

        ChartView{
            height: dp(400)
            width: Math.min( dp(700), parent.parent.width * 0.8)
            antialiasing: true


            SplineSeries{
                name: "Historial Volumen"
                id: volumeSeries
                axisX: ValueAxis{
                    min: 0
                    max: 100
                }
                axisY: ValueAxis{
                    min:0
                    max:127
                }
                property int actualCount : 0
                function addValue(val){
                    if(volumeSeries.count > 100){
                        removePoints(0,1);
                        axisX.min++;
                        axisX.max++;
                    }
                    actualCount++;
                    append(actualCount,val);
                }
            }
        }

    }

    Connections{
        target: udpSender
        onDataChange: {
            volumeAverage.addValue(volume)
            volumeSeries.append(volumeSeries.count,volume)
            mostPlayedNote.addNote(currentNote)
        }
    }
}
