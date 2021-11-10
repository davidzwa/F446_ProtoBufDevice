import json
import os
import errno
import time

from utils.nickname import generate

class DataStore(object):
    def __init__(self):
        self.__data_cache = None
        self.__devices = None
        self.__data_file = "./data/devices.json"

    def __get_default_json(self):
        return {
            "devices": []
        }

    def ensure_folder_created(self):
        if not os.path.exists(os.path.dirname(self.__data_file)):
            try:
                os.makedirs(os.path.dirname(self.__data_file))
            except OSError as exc:  # Guard against race condition
                if exc.errno != errno.EEXIST:
                    raise

    def __read_data_file(self):
        f = open(self.__data_file, "r")
        buffer = f.read()
        f.close()

        return buffer

    def __write_data_file(self, buffer):
        f = open(self.__data_file, "w")
        f.write(buffer)
        f.close()

    def set_devices(self):
        self.__devices = self.__data_cache["devices"]

    def add_device(self, id, meta={}):
        new_device = {
            "id": id,
            "nickname": generate(),
            "registered_at": int(time.time()),
            "is_gateway": False,
            "meta": meta
        }
        self.__devices.append(new_device)
        self.persist_json()

        return new_device

    def get_devices(self):
        return self.__devices

    def get_device(self, id, create_if_missing=False):
        devices_found = [d for d in self.get_devices() if d["id"] == id]

        if not len(devices_found) and create_if_missing:
            return self.add_device(id, None)

        return devices_found[0]

    def persist_json(self):
        serialized_data = json.dumps(self.__data_cache, indent=True)
        self.__write_data_file(serialized_data)

    def load_json(self):
        if not os.path.exists(self.__data_file):
            self.ensure_folder_created()
            self.__data_cache = self.__get_default_json()

            self.persist_json()
        else:
            data_buffer = self.__read_data_file()
            self.__data_cache = json.loads(data_buffer)

        self.set_devices()

    # def check_device_exists():


data_store = DataStore()
