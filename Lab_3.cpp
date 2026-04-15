#include <iostream>
#include <string>

using namespace std;

class Sensor {
    const int id;
    double value;
    mutable int accessCount;

public:
    Sensor(int id, double value) : id(id), value(value), accessCount(0) {}
    Sensor() : Sensor(0, 0.0) {}
    Sensor(const Sensor& other) : id(other.id), value(other.value), accessCount(0) {
        cout << "Kopiowanie sensora ID: " << id << endl;
    }
    double getValue() const {
        accessCount++;
        return value;
    }
    void setValue(double v) {
        value = v;
    }
    int getChecks() const {
        return accessCount;
    }
    ~Sensor() {
        cout << "Usuniecie czujnika o ID: " << id << endl;
    }
    friend class ClimateController;
};

class ClimateController {
    string roomName;
    Sensor ambientSensor;
    const Sensor& referenceSensor;
    class DiagnosticLog {
    public:
        void print(string msg) {
            cout << "[DIAG] " << msg << endl;
        }
    };

public:
    ClimateController(string name, int sensorId, double initialTemp, const Sensor& ref): roomName(name), ambientSensor(sensorId, initialTemp), referenceSensor(ref) {
    }
    void compareWithBenchmark() const {
        auto loc = ambientSensor.getValue();
        auto ref = referenceSensor.getValue();
        cout << "Roznica temperatur (" << roomName << "): " << (loc - ref) << " C" << endl;
    }
    void calibrate(double offset) {
        ambientSensor.value += offset;
    }
    const Sensor& getInternalSensor() const {
        return ambientSensor;
    }
};
void emergencyAlert(const Sensor& s) {
    if (s.getValue() > 40.0) {
        cout << "Alert" << endl;
    }
}
int main() {
    Sensor outdoorStation(100, 15.5);
    string name;
    cout << "Podaj nazwe pomieszczenia: ";
    cin >> name;
    ClimateController controller(name, 10, 20.0, outdoorStation);
    controller.compareWithBenchmark();
    decltype(controller.getInternalSensor().getValue()) cur;
    cur = controller.getInternalSensor().getValue();
    cout << "Aktualna temperatura: " << cur << endl;
    emergencyAlert(controller.getInternalSensor());
    return 0;
}