using System;
using System.Windows.Forms;

namespace Week2
{
	public class Animator
	{
		public bool IsAnimating => _timer.Enabled;
		
		private readonly Form1 _form;
		private readonly Timer _timer;
		
		private int _phase;
		private float _currentScale;
		private float _currentRotationX;
		private float _currentRotationY;
		private float _currentTheta;
		private float _currentPhi;
		
		private delegate T Transformation<T>(float f);

		public Animator(Form1 form)
		{
			_form = form;
			
			_timer = new Timer();
			_timer.Interval = 50;
			_timer.Tick += Animate;
			
			SetInitialValues();
		}

		private void SetInitialValues()
		{
			_phase = 0;
			_currentScale = 1f;
			_currentRotationX = 0f;
			_currentRotationY = 0f;
			_currentTheta = Form1.StartTheta;
			_currentPhi = Form1.StartPhi;
		}

		public void StartAnimation()
		{
			_timer.Enabled = true;
		}

		public void ResetAnimation()
		{
			_timer.Stop();
			SetInitialValues();
		}

		private void Animate(object sender, EventArgs e)
		{
			switch (_phase)
			{
				case 0:
					_form.ScaleMatrix = AnimateValue(Matrix.Scale, ref _currentScale, .01f, 1.49f, () => _phase++);
					_form.Theta = AnimateValue(f => f, ref _currentTheta, -.02f, float.NegativeInfinity);
					break;
				case 1:
					_form.ScaleMatrix = AnimateValue(Matrix.Scale, ref _currentScale, -.01f, 1f, () => _phase++);
					_form.Theta = AnimateValue(f => f, ref _currentTheta, -.02f, float.NegativeInfinity);
					break;
				case 2:
					_form.RotationMatrix = AnimateValue(Matrix.RotateX, ref _currentRotationX, 1, 45, () => _phase++);
					_form.Theta = AnimateValue(f => f, ref _currentTheta, -.02f, float.NegativeInfinity);
					break;
				case 3:
					_form.RotationMatrix = AnimateValue(Matrix.RotateX, ref _currentRotationX, -1, 0, () => _phase++);
					_form.Theta = AnimateValue(f => f, ref _currentTheta, -.02f, float.NegativeInfinity);
					break;
				case 4:
					_form.RotationMatrix = AnimateValue(Matrix.RotateY, ref _currentRotationY, 1, 45, () => _phase++);
					_form.Phi = AnimateValue(f => f, ref _currentPhi, .01f, float.PositiveInfinity);
					break;
				case 5:
					_form.RotationMatrix = AnimateValue(Matrix.RotateY, ref _currentRotationY, -1, 0, () => _phase++);
					_form.Phi = AnimateValue(f => f, ref _currentPhi, .01f, float.PositiveInfinity);
					break;
				case 6:
					AnimateToDefault();
					break;
				case 7:
					SetInitialValues();
					return;
			}

			_form.Invalidate();
		}

		private void AnimateToDefault()
		{
			bool thetaAtDefault = false;
			bool phiAtDefault = false;
			_form.Theta = AnimateValue(f => f, ref _currentTheta, .02f, Form1.StartTheta, () => thetaAtDefault = true);
			_form.Phi = AnimateValue(f => f, ref _currentPhi, -.01f, Form1.StartPhi, () => phiAtDefault = true);

			if (thetaAtDefault && phiAtDefault)
			{
				_phase++;
			}
		}

		private T AnimateValue<T>(Transformation<T> t, ref float currentValue, float stepSize, float limit, Action callback = null)
		{
			bool shouldAnimate = stepSize > 0 ? currentValue < limit : currentValue > limit;
			if (shouldAnimate)
			{
				currentValue += stepSize;
			}
			else
			{
				callback?.Invoke();
			}

			return t(currentValue);
		}
	}
}