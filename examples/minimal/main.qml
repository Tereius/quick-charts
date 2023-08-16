import QtQuick
import QtQuick.Controls
import org.kde.quickcharts 1.0 as Charts
import org.kde.quickcharts.controls 1.0 as ChartsControls


ApplicationWindow
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Minimal LineChart example")

    ListModel {
        id: lineModel;
        dynamicRoles: true;

        Component.onCompleted: {
            append({label: "Item 1", value1: 10, value2: 15, value3: 20})
            append({label: "Item 2", value1: 15, value2: 25, value3: 25})
            append({label: "Item 3", value1: 15, value2: 20, value3: 30})
            append({label: "Item 4", value1: 10, value2: 10, value3: 35})
            append({label: "Item 5", value1: 20, value2:  5, value3: 40})
            append({label: "Item 6", value1: 40, value2: 50, value3: 34})
            append({label: "Item 6", value1: 20, value2: 34, value3: 66})
            append({label: "Item 8", value1: 10, value2: 56, value3: 34})
        }
    }

	SwipeView {
		id: view

		currentIndex: 1
		anchors.fill: parent

		Item {
			id: firstPage
		}

		ChartsControls.LineChartControl {
			id: lineChart

			valueSources: [
				Charts.ModelSource { roleName: "value1"; model: lineModel },
				Charts.ModelSource { roleName: "value2"; model: lineModel },
				Charts.ModelSource { roleName: "value3"; model: lineModel }
			]

			names: ["Example 1", "Example 2", "Example 3"]

			pointDelegate: Item {
				Rectangle {
					anchors.centerIn: parent
					width: 10
					height: width
					radius: width / 2;
					color: parent.Charts.LineChart.color

					MouseArea {
						id: mouse
						anchors.fill: parent
						hoverEnabled: true
					}

					ToolTip.visible: mouse.containsMouse
					ToolTip.text: "%1: %2".arg(parent.Charts.LineChart.name).arg(parent.Charts.LineChart.value)
				}
			}
		}
	}
}
