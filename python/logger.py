"""
Serial CSV logger for the ESP32 Environmental Sensor Node.
"""

from __future__ import annotations

import argparse
import csv
import sys
import time
from pathlib import Path

try:
    import serial
except ImportError as exc:
    raise SystemExit(
        "Missing dependency: pyserial. Install it with `pip install pyserial`."
    ) from exc


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Log ESP32 sensor CSV data from serial.")
    parser.add_argument("--port", required=True, help="Serial port, e.g. COM5 or /dev/ttyUSB0")
    parser.add_argument("--baud", type=int, default=115200, help="Serial baud rate")
    parser.add_argument("--out", default="data_log.csv", help="Output CSV filename")
    parser.add_argument("--timeout", type=float, default=2.0, help="Serial read timeout in seconds")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    out_path = Path(args.out)

    print(f"Opening {args.port} at {args.baud} baud...")
    print(f"Writing to {out_path.resolve()}")
    print("Press Ctrl+C to stop.\n")

    with serial.Serial(args.port, args.baud, timeout=args.timeout) as ser, out_path.open(
        "a", newline=""
    ) as csv_file:
        writer = csv.writer(csv_file)

        while True:
            try:
                raw = ser.readline().decode("utf-8", errors="replace").strip()
                if not raw:
                    continue

                print(raw)

                # Keep the firmware's CSV format, but add a host-side timestamp.
                row = raw.split(",")
                writer.writerow([time.time(), *row])
                csv_file.flush()

            except KeyboardInterrupt:
                print("\nStopped logging.")
                return 0
            except Exception as exc:  # Keep logger alive during occasional malformed serial reads.
                print(f"Logger warning: {exc}", file=sys.stderr)


if __name__ == "__main__":
    raise SystemExit(main())
"""
Examples:
    python logger.py --port COM5 --baud 115200 --out data_log.csv
    python logger.py --port /dev/ttyUSB0 --baud 115200 --out data_log.csv
"""
