/*
* Copyright (c) 2007-2010 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

/* 
* ALTERED in various parts by Hazard (hazard_x@gmx.net) to adapt it to it's 
* role in the GTA4 .Net ScriptHook. 2009-2011
*/

#pragma once
#pragma managed

namespace GTA {

	value class Matrix;
	value class Vector3;

	[System::SerializableAttribute]
	[System::Runtime::InteropServices::StructLayout( System::Runtime::InteropServices::LayoutKind::Sequential )]
	public value class Quaternion {
	public:
		/// <summary>
		/// Gets or sets the X component of the quaternion.
		/// </summary>
		/// <value>The X component of the quaternion.</value>
		float X;

		/// <summary>
		/// Gets or sets the Y component of the quaternion.
		/// </summary>
		/// <value>The Y component of the quaternion.</value>
		float Y;

		/// <summary>
		/// Gets or sets the Z component of the quaternion.
		/// </summary>
		/// <value>The Z component of the quaternion.</value>
		float Z;

		/// <summary>
		/// Gets or sets the W component of the quaternion.
		/// </summary>
		/// <value>The W component of the quaternion.</value>
		float W;

		/// <summary>
		/// Initializes a new instance of the <see cref="Quaternion"/> structure.
		/// </summary>
		/// <param name="x">The X component of the quaternion.</param>
		/// <param name="y">The Y component of the quaternion.</param>
		/// <param name="z">The Z component of the quaternion.</param>
		/// <param name="w">The W component of the quaternion.</param>
		Quaternion( float x, float y, float z, float w );

		/// <summary>
		/// Initializes a new instance of the <see cref="Quaternion"/> structure.
		/// </summary>
		/// <param name="value">A <see cref="Vector3"/> containing the first three values of the quaternion.</param>
		/// <param name="w">The W component of the quaternion.</param>
		Quaternion( Vector3 value, float w );

		/// <summary>
		/// Gets the identity <see cref="Quaternion"/> (0, 0, 0, 1).
		/// </summary>
		static property Quaternion Identity { Quaternion get(); }

		/// <summary>
		/// Gets the axis components of the quaternion.
		/// </summary>
		property Vector3 Axis { Vector3 get(); }

		/// <summary>
		/// Gets the angle of the quaternion.
		/// </summary>
		property float Angle { float get(); }

		/// <summary>
		/// Calculates the length of the quaternion.
		/// </summary>
		/// <returns>The length of the quaternion.</returns>
		float Length();

		/// <summary>
		/// Converts the quaternion into a unit quaternion.
		/// </summary>
		void Normalize();

		/// <summary>
		/// Conjugates the quaternion.
		/// </summary>
		void Conjugate();

		/// <summary>
		/// Conjugates and renormalizes the quaternion.
		/// </summary>
		void Invert();

		/// <summary>
		/// Adds two quaternions.
		/// </summary>
		/// <param name="left">The first quaternion to add.</param>
		/// <param name="right">The second quaternion to add.</param>
		/// <returns>The sum of the two quaternions.</returns>
		static Quaternion Add( Quaternion left, Quaternion right );

		/// <summary>
		/// Divides a quaternion by another.
		/// </summary>
		/// <param name="left">The first quaternion to divide.</param>
		/// <param name="right">The second quaternion to divide.</param>
		/// <returns>The divided quaternion.</returns>
		static Quaternion Divide( Quaternion left, Quaternion right );

		/// <summary>
		/// Calculates the dot product of two quaternions.
		/// </summary>
		/// <param name="left">First source quaternion.</param>
		/// <param name="right">Second source quaternion.</param>
		/// <returns>The dot product of the two quaternions.</returns>
		static float Dot( Quaternion left, Quaternion right );

		/// <summary>
		/// Conjugates and renormalizes the quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to conjugate and renormalize.</param>
		/// <returns>The conjugated and renormalized quaternion.</returns>
		static Quaternion Invert( Quaternion quaternion );

		/// <summary>
		/// Performs a linear interpolation between two quaternion.
		/// </summary>
		/// <param name="start">Start quaternion.</param>
		/// <param name="end">End quaternion.</param>
		/// <param name="amount">Value between 0 and 1 indicating the weight of <paramref name="end"/>.</param>
		/// <returns>The linear interpolation of the two quaternions.</returns>
		/// <remarks>
		/// This method performs the linear interpolation based on the following formula.
		/// <code>start + (end - start) * amount</code>
		/// Passing <paramref name="amount"/> a value of 0 will cause <paramref name="start"/> to be returned; a value of 1 will cause <paramref name="end"/> to be returned. 
		/// </remarks>
		static Quaternion Lerp( Quaternion start, Quaternion end, float amount );

		/// <summary>
		/// Modulates a quaternion by another.
		/// </summary>
		/// <param name="left">The first quaternion to modulate.</param>
		/// <param name="right">The second quaternion to modulate.</param>
		/// <returns>The modulated quaternion.</returns>
		static Quaternion Multiply( Quaternion left, Quaternion right );

		/// <summary>
		/// Scales a quaternion by the given value.
		/// </summary>
		/// <param name="quaternion">The quaternion to scale.</param>
		/// <param name="scale">The amount by which to scale the quaternion.</param>
		/// <returns>The scaled quaternion.</returns>
		static Quaternion Multiply( Quaternion quaternion, float scale );

		/// <summary>
		/// Reverses the direction of a given quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to negate.</param>
		/// <returns>A quaternion facing in the opposite direction.</returns>
		static Quaternion Negate( Quaternion quaternion );

		/// <summary>
		/// Converts the quaternion into a unit quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to normalize.</param>
		/// <returns>The normalized quaternion.</returns>
		static Quaternion Normalize( Quaternion quaternion );

		/// <summary>
		/// Creates a quaternion given a rotation and an axis.
		/// </summary>
		/// <param name="axis">The axis of rotation.</param>
		/// <param name="angle">The angle of rotation.</param>
		/// <returns>The newly created quaternion.</returns>
		static Quaternion RotationAxis( Vector3 axis, float angle );

		/// <summary>
		/// Creates a quaternion given a rotation matrix.
		/// </summary>
		/// <param name="matrix">The rotation matrix.</param>
		/// <returns>The newly created quaternion.</returns>
		static Quaternion RotationMatrix( Matrix matrix );

		/// <summary>
		/// Creates a quaternion given a yaw, pitch, and roll value.
		/// </summary>
		/// <param name="yaw">The yaw of rotation.</param>
		/// <param name="pitch">The pitch of rotation.</param>
		/// <param name="roll">The roll of rotation.</param>
		/// <returns>The newly created quaternion.</returns>
		static Quaternion RotationYawPitchRoll( float yaw, float pitch, float roll );

		/// <summary>
		/// Subtracts two quaternions.
		/// </summary>
		/// <param name="left">The first quaternion to subtract.</param>
		/// <param name="right">The second quaternion to subtract.</param>
		/// <returns>The difference of the two quaternions.</returns>
		static Quaternion Subtract( Quaternion left, Quaternion right );

		/// <summary>
		/// Multiplies a quaternion by another.
		/// </summary>
		/// <param name="left">The first quaternion to multiply.</param>
		/// <param name="right">The second quaternion to multiply.</param>
		/// <returns>The multiplied quaternion.</returns>
		static Quaternion operator * ( Quaternion left, Quaternion right );

		/// <summary>
		/// Scales a quaternion by the given value.
		/// </summary>
		/// <param name="quaternion">The quaternion to scale.</param>
		/// <param name="scale">The amount by which to scale the quaternion.</param>
		/// <returns>The scaled quaternion.</returns>
		static Quaternion operator * ( Quaternion quaternion, float scale );

		/// <summary>
		/// Scales a quaternion by the given value.
		/// </summary>
		/// <param name="quaternion">The quaternion to scale.</param>
		/// <param name="scale">The amount by which to scale the quaternion.</param>
		/// <returns>The scaled quaternion.</returns>
		static Quaternion operator * ( float scale, Quaternion quaternion );

		/// <summary>
		/// Divides a quaternion by another.
		/// </summary>
		/// <param name="left">The first quaternion to divide.</param>
		/// <param name="right">The second quaternion to divide.</param>
		/// <returns>The divided quaternion.</returns>
		static Quaternion operator / ( Quaternion left, float right );

		/// <summary>
		/// Adds two quaternions.
		/// </summary>
		/// <param name="left">The first quaternion to add.</param>
		/// <param name="right">The second quaternion to add.</param>
		/// <returns>The sum of the two quaternions.</returns>
		static Quaternion operator + ( Quaternion left, Quaternion right );

		/// <summary>
		/// Subtracts two quaternions.
		/// </summary>
		/// <param name="left">The first quaternion to subtract.</param>
		/// <param name="right">The second quaternion to subtract.</param>
		/// <returns>The difference of the two quaternions.</returns>
		static Quaternion operator - ( Quaternion left, Quaternion right );

		/// <summary>
		/// Reverses the direction of a given quaternion.
		/// </summary>
		/// <param name="quaternion">The quaternion to negate.</param>
		/// <returns>A quaternion facing in the opposite direction.</returns>
		static Quaternion operator - ( Quaternion quaternion );

		/// <summary>
		/// Tests for equality between two objects.
		/// </summary>
		/// <param name="left">The first value to compare.</param>
		/// <param name="right">The second value to compare.</param>
		/// <returns><c>true</c> if <paramref name="left"/> has the same value as <paramref name="right"/>; otherwise, <c>false</c>.</returns>
		static bool operator == ( Quaternion left, Quaternion right );

		/// <summary>
		/// Tests for inequality between two objects.
		/// </summary>
		/// <param name="left">The first value to compare.</param>
		/// <param name="right">The second value to compare.</param>
		/// <returns><c>true</c> if <paramref name="left"/> has a different value than <paramref name="right"/>; otherwise, <c>false</c>.</returns>
		static bool operator != ( Quaternion left, Quaternion right );

		/// <summary>
		/// Converts the value of the object to its equivalent string representation.
		/// </summary>
		/// <returns>The string representation of the value of this instance.</returns>
		virtual System::String^ ToString() override;

		/// <summary>
		/// Returns the hash code for this instance.
		/// </summary>
		/// <returns>A 32-bit signed integer hash code.</returns>
		virtual int GetHashCode() override;

		/// <summary>
		/// Returns a value that indicates whether the current instance is equal to a specified object. 
		/// </summary>
		/// <param name="obj">Object to make the comparison with.</param>
		/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
		virtual bool Equals( System::Object^ obj ) override;

		/// <summary>
		/// Returns a value that indicates whether the current instance is equal to the specified object. 
		/// </summary>
		/// <param name="other">Object to make the comparison with.</param>
		/// <returns><c>true</c> if the current instance is equal to the specified object; <c>false</c> otherwise.</returns>
		virtual bool Equals( Quaternion other );

		/// <summary>
		/// Determines whether the specified object instances are considered equal. 
		/// </summary>
		/// <param name="value1"></param>
		/// <param name="value2"></param>
		/// <returns><c>true</c> if <paramref name="value1"/> is the same instance as <paramref name="value2"/> or 
		/// if both are <c>null</c> references or if <c>value1.Equals(value2)</c> returns <c>true</c>; otherwise, <c>false</c>.</returns>
		static bool Equals( Quaternion% value1, Quaternion% value2 );


		// ### my stuff ###

		//static Quaternion FromRotationAxis(Vector3 axis, float angle);
		//static Quaternion FromYawPitchRoll(float yaw, float pitch, float roll);
		static Quaternion FromRotation(Vector3 Rotation);
		Vector3 ToRotation();

		System::String^ ToString(System::String^ Seperator, int Digits);

	};

}