from setuptools import setup
import os

package_name = 'counter_publisher_py'

setup(
    name=package_name,
    version='0.0.1',
    packages=[package_name],
    package_dir={package_name: 'src/' + package_name},
    data_files=[
        (os.path.join('share', package_name), ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Your Name',
    maintainer_email='your.email@example.com',
    description='Publisher en Python para ROS 2',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'counter_publisher = counter_publisher_py.counter_publisher:main',
        ],
    },
)