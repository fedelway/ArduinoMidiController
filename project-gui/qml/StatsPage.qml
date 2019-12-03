import Felgo 3.0
import QtQuick 2.0
import QtCharts 2.3

Page {
    Column{
        anchors.centerIn: parent
        InfoLabel{
            id: mostPlayedNote
            fieldName: "Nota más tocada: "
            property var notesPlayed : [{note:69,count:10},{note:71,count:17}];
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

        AppButton{
            onClicked: mostPlayedNote.addNote(69);
        }

        ChartView{
            height: dp(250)
            width: dp(250)
            legend.visible: true
            antialiasing: true

            PieSeries{
                id: notesChart
                holeSize: 0.25

                function generateChart(data){
                    clear();
                    data.forEach(function(e){
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
            property var avgData : ({sum: 0, count: 0});
            function addValue(value){
                avgData.sum += value;
                avgData.count++;
                change(avgData.sum / avgData.count)
            }
        }
    }

    Connections{
        target: udpSender
        onDataChange: {
            volumeAverage.addValue(volume)
            mostPlayedNote.addNote(currentNote)
        }
    }
}
