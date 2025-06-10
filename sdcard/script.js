document.addEventListener('DOMContentLoaded', () => {
    let isMapowanieMode = false;
    let isStartActive = false;
    let file1Data = [], file2Data = [];

    const mapowanieButton = document.getElementById('mapowanie');
    const patrolowanieButton = document.getElementById('patrolowanie');
    const startButton = document.getElementById('start');
    const stopButton = document.getElementById('stop');
    const compareButton = document.getElementById('compare');

    function loadCSV(url, tableId) {
        fetch(url)
            .then(response => response.text())
            .then(csvData => {
                const data = parseCSV(csvData);
                displayCSVData(data, tableId);
                if (tableId === 'csv1-table') {
                    file1Data = data;
                } else if (tableId === 'csv2-table') {
                    file2Data = data;
                }
            })
            .catch(error => console.error('Error loading CSV:', error));
    }

    loadCSV('/map.csv', 'csv2-table');
    loadCSV('/patrol.csv', 'csv1-table');

    setInterval(() => {
        loadCSV('/map.csv', 'csv2-table');
        loadCSV('/patrol.csv', 'csv1-table');
    }, 10000);

    mapowanieButton.addEventListener('click', () => {
        fetch('/mapowanie');
        isMapowanieMode = true;
        updateButtons();
    });

    patrolowanieButton.addEventListener('click', () => {
        fetch('/patrolowanie');
        isMapowanieMode = false;
        updateButtons();
    });

    startButton.addEventListener('click', () => {
        fetch('/start');
        isStartActive = true;
        updateStartButton();
    });

    stopButton.addEventListener('click', () => {
        fetch('/stop');
        isStartActive = false;
        updateStartButton();
    });

    compareButton.addEventListener('click', () => {
        if (file1Data.length > 0 && file2Data.length > 0) {
            compareCSVContent(file1Data, file2Data);
        } else {
            alert("Najpierw załaduj oba pliki CSV.");
        }
    });

    function updateButtons() {
        mapowanieButton.classList.toggle('active', isMapowanieMode);
        patrolowanieButton.classList.toggle('active', !isMapowanieMode);
    }

    function updateStartButton() {
        startButton.classList.toggle('active', isStartActive);
        stopButton.classList.toggle('active', !isStartActive);
    }

    function parseCSV(csvData) {
        const lines = csvData.trim().split('\n');
        const headers = lines[0].split(',');
        return lines.slice(1).map(line => {
            const values = line.split(',');
            return headers.reduce((obj, header, index) => {
                const value = values[index].trim();
                obj[header] = isNaN(value) ? value : parseFloat(value);
                return obj;
            }, {});
        });
    }

    function displayCSVData(data, tableId) {
        const tableBody = document.querySelector(`#${tableId} tbody`);
        tableBody.innerHTML = '';

        data.forEach(row => {
            const tableRow = document.createElement('tr');
            for (let key in row) {
                const tableCell = document.createElement('td');
                tableCell.textContent = row[key];
                tableRow.appendChild(tableCell);
            }
            tableBody.appendChild(tableRow);
        });
    }

    function compareCSVContent(file1Data, file2Data) {
        const csv1TableBody = document.querySelector('#csv1-table tbody');
        const csv2TableBody = document.querySelector('#csv2-table tbody');

        const rows1 = csv1TableBody.querySelectorAll('tr');
        const rows2 = csv2TableBody.querySelectorAll('tr');

        rows1.forEach((row1, index) => {
            const cells1 = row1.querySelectorAll('td');
            const row2 = rows2[index];
            const cells2 = row2 ? row2.querySelectorAll('td') : [];

            cells1.forEach((cell1, cellIndex) => {
                const rawValue1 = cell1.textContent.trim();
                const rawValue2 = cells2[cellIndex] ? cells2[cellIndex].textContent.trim() : '';

                const value1 = rawValue1 === '' ? -1 : parseFloat(rawValue1);
                const value2 = rawValue2 === '' ? -1 : parseFloat(rawValue2);

                const header = document.querySelector(`#csv1-table thead th:nth-child(${cellIndex + 1})`).textContent;

                if (header && cellIndex > 0) {
                    const errorMargin = header.includes('Wheel') ? 0.42 : 10;

                    if (value1 === -1 || value2 === -1 || isNaN(value1) || isNaN(value2)) {
                        cell1.classList.add('highlight-orange');
                        if (cells2[cellIndex]) cells2[cellIndex].classList.add('highlight-orange');
                    } else {
                        const difference = Math.abs(value1 - value2);
                        if (difference > errorMargin) {
                            cell1.classList.add('highlight-red');
                            if (cells2[cellIndex]) cells2[cellIndex].classList.add('highlight-red');
                        } else {
                            cell1.classList.add('highlight-green');
                            if (cells2[cellIndex]) cells2[cellIndex].classList.add('highlight-green');
                        }
                    }
                }
            });
        });
    }
});
